#include "imgCompress.h"
#include "dp.h"



imgCompress::imgCompress(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.progressBar->setVisible(false);
	setAcceptDrops(true);

	connect(this, &imgCompress::sendProgress, ui.progressBar, &QProgressBar::setValue);
	connect(ui.md5Button, &QPushButton::clicked, this, &imgCompress::newMd5Window);
}


void imgCompress::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void imgCompress::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;
	QString filename = urls.first().toLocalFile();
	this->filename = filename;
	bool haveChina = filename.contains(QRegExp("[\\x4e00-\\x9fa5]+"));
	if (haveChina)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("路径不能包含中文"));
		return;
	}
	//判断后缀为多少，来看是要采取压缩策略还是采取解压策略
	QString format = filename.mid(filename.lastIndexOf(".") + 1);
	if (format == "Img")
	{
		decompressReadImag();
		decompress();
	}
	else if(format == "bmp")
	{
		compressReadImag();//打开inFile将数据读入到inData中
		compress();
	}
	else 
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("需要bmp格式"));
	}
}


void imgCompress::compressReadImag()
{
	QByteArray ba = filename.toLatin1();
	char *temptemp = ba.data();
	inFile = fopen(temptemp, "rb");
	fread(&fileHeader, sizeof(fileHeader), 1, inFile);
	fread(&infoHeader, sizeof(infoHeader), 1, inFile);
	pallet = new UCHAR[fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader) + 1];
	fread(pallet, fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader), 1, inFile);
	pallet[fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader)] = '\0';


	int height = infoHeader.biHeight;
	int width = infoHeader.biWidth;
	fileSize = width * height;

	UCHAR *temp = new UCHAR[fileSize];
	fread(temp, sizeof(UCHAR), fileSize, inFile);
	inData = new UCHAR[fileSize + 1];
	for (int i = 0; i < fileSize; i++)
		inData[i + 1] = temp[i];
	fclose(inFile);
}

void imgCompress::compress()
{
	unsigned int writeBuf[256];//1kb就写入
	for (int i = 0; i < 256;i++)
		writeBuf[i] = 0;
	unsigned char bit;
	unsigned char num;
	unsigned int cnt = 1;
	unsigned int currentSize = 0;
	unsigned int index = 0;
	//计算出分段信息
	getSegment(fileSize, segment, segmentBit);
	
	QString _preFileNmae = filename.split(".")[0];
	_preFileNmae += ".Img";
	QByteArray _ba = _preFileNmae.toLatin1();
	char *_temp = _ba.data();
	outFile = fopen(_temp, "wb");
	
	int debug_sum = 0;
	//跳过一个char
	fseek(outFile, 1, SEEK_CUR);
	//写入头
	fwrite(&fileHeader, sizeof(fileHeader), 1, outFile);
	fwrite(&infoHeader, sizeof(infoHeader), 1, outFile);
	fwrite(pallet, fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader), 1, outFile);

	for (int i = 0; i < segment.size(); i++)
	{
		debug_sum += segment[i];
		num = segment[i];
		bit = segmentBit[i];
		putInt(writeBuf, index, currentSize, num, 8);
		putInt(writeBuf, index, currentSize, bit, 3);
		for (int j = 0; j < num; j++)
		{
			putInt(writeBuf, index, currentSize, inData[cnt++], bit);
		}
	}
	fwrite(writeBuf, 4, index+1, outFile);
	//放入currentSize
	fseek(outFile, 0, SEEK_SET);
	fputc(char(currentSize), outFile);
	fclose(outFile);
}

void imgCompress::decompressReadImag()
{
	QByteArray _ba = filename.toLatin1();
	char *_temptemp = _ba.data();
	inFile = fopen(_temptemp, "rb");
	
	rest = fgetc(inFile);
	fread(&fileHeader, sizeof(fileHeader), 1, inFile);
	fread(&infoHeader, sizeof(infoHeader), 1, inFile);
	pallet = new UCHAR[fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader) + 1];
	fread(pallet, fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader), 1, inFile);
	pallet[fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader)] = '\0';

	int start = ftell(inFile);
	fseek(inFile, 0, SEEK_END);		
	int end = ftell(inFile);
	fileSize = end - start;
	buf = new unsigned int[fileSize/4];
	fseek(inFile, 0, SEEK_SET);
	fseek(inFile, fileHeader.bfOffBits+1, SEEK_CUR);

	fread(buf, 4, fileSize / 4, inFile);
	fclose(inFile);	
}

void imgCompress::decompress()
{
	//对inData进行解压，将解压出来的outData放入到outFile中
	QString _preFileName = filename.split(".")[0];
	_preFileName += ".bmp";
	QByteArray _ba = _preFileName.toLatin1();
	char *_temp = _ba.data();
	outFile = fopen(_temp, "wb");
	fwrite(&fileHeader, sizeof(fileHeader), 1, outFile);
	fwrite(&infoHeader, sizeof(infoHeader), 1, outFile);
	fwrite(pallet, fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader), 1, outFile);


	unsigned int index = 0;
	unsigned int currentSize = 0;
	unsigned int sum = 0;
	while (true)
	{
		if (putChar(index, currentSize,sum) == false)
			break;
	}

	
	fclose(outFile);
}



//分段信息放入segment和segmentBit中
void imgCompress::getSegment(int n, vector<int>& segment, vector<int>& segmentBit)
{
	unsigned int *s = new unsigned int[n + 1];
	unsigned int *l = new unsigned int[n + 1];
	unsigned int *b = new unsigned int[n + 1];

	int Lmax = 256, header = 11;
	s[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		b[i] = length(inData[i]);//计算像素点p需要的存储位数  
		unsigned int bmax = b[i];
		s[i] = s[i - 1] + bmax;
		l[i] = 1;
		for (int j = 2; j <= i && j < Lmax; j++)
		{
			if (bmax<b[i - j + 1])
				bmax = b[i - j + 1];
			if (s[i]>s[i - j] + j * bmax)
			{
				s[i] = s[i - j] + j * bmax;
				l[i] = j;
			}
		}
		s[i] += header;
	}



	int m = 0;
	Traceback(n, m, s, l);
	s[m] = n;
	for (int i = 1; i <= m; i++)
	{
		l[i] = l[s[i]];
		int Max = 0;
		for (int j = s[i - 1] + 1; j <= s[i]; j++)
		{
			if (b[j] > Max)
				Max = b[j];
		}
		b[i] = Max;
	}



	for (int j = 1; j <= m; j++)
	{
		segment.push_back(l[j]);
		segmentBit.push_back(b[j]);
	}
	delete[] s;
	delete[] l;
	delete[] b;
}

void imgCompress::newMd5Window()
{
	sonMain *sonWindow = new sonMain;
	sonWindow->setWindowTitle(QStringLiteral("校验文件"));

	sonWindow->show();
}

//压缩放入int
void imgCompress::putInt(unsigned int writeBuf[], unsigned int &index, unsigned int &currentSize, unsigned int num, unsigned int bitNum)
{
	if (bitNum == 3 && num == 8)
		num = 0;
	if (currentSize + bitNum >= 32)
	{
		unsigned int offset = 32 - currentSize;
		unsigned int tempNum = num;
		tempNum = tempNum >> (bitNum - offset);
		writeBuf[index] <<= offset;
		writeBuf[index] = writeBuf[index] ^ tempNum;
		index++;
		if (index == 256)
		{
			fwrite(writeBuf, 4, 256, outFile);
			for (int i = 0; i < 256; i++)
				writeBuf[i] = 0;
			index = 0;
		}
		if (currentSize + bitNum != 32)
		{
			num = (num << (32 - bitNum + offset));
			num = (num >> (32 - bitNum + offset));
			writeBuf[index] = writeBuf[index] ^ num;
		}
		currentSize = currentSize + bitNum - 32;
	}
	else 
	{
		currentSize += bitNum;
		writeBuf[index] <<= bitNum;
		writeBuf[index] = writeBuf[index] ^ num;
	}
}


//解压放入char
bool imgCompress::putChar(unsigned int &index, unsigned int &currentSize,unsigned int &sum)
{
	unsigned int num;
	unsigned int bitNum;
	unsigned int temp;
	unsigned int tempRight;
	unsigned char ch;
	num = buf[index];
	if (currentSize + 8 > 32)
	{
		temp = buf[index];
		unsigned int offset = 32 - currentSize;
		temp = temp << currentSize;
		temp = temp >> currentSize;
		currentSize = currentSize + 8 - 32;
		temp = temp << (8 - offset);
		index++;
		num = buf[index];
		num = num >> (32 - (8 - offset));
		num = temp ^ num;
	}
	else if (currentSize + 8 == 32)
	{
		temp = buf[index];
		temp = temp << currentSize;
		temp = temp >> currentSize;
		num = temp;
		index++;
		currentSize = 0;
	}
	else 
	{
		num = num << currentSize;
		num = num >> 24;
		currentSize += 8;
	}
	if (num == 0)
		return false;
	sum += num;

	bitNum = buf[index];
	if (currentSize + 3 > 32)
	{
		temp = buf[index];
		unsigned int offset = 32 - currentSize;
		temp = temp << currentSize;
		temp = temp >> currentSize;
		currentSize = currentSize + 3 - 32;
		temp = temp << (3 - offset);
		index++;
		bitNum = buf[index];
		bitNum = bitNum >> (32 - (3 - offset));
		bitNum = temp ^ bitNum;
	}
	else if (currentSize + 3 == 32)
	{
		temp = buf[index];
		temp = temp << currentSize;
		temp = temp >> currentSize;
		bitNum = temp;
		index++;
		currentSize = 0;
	}
	else 
	{
		bitNum = bitNum << currentSize;
		bitNum = bitNum >> 29;
		currentSize += 3;
	}
	if (bitNum == 0)
		bitNum = 8;



	for (int i = 0; i < num; i++)
	{
		if (currentSize + bitNum > 32)
		{
			temp = buf[index];
			unsigned int offset = 32 - currentSize;
			temp = temp << currentSize;
			temp = temp >> currentSize;
			currentSize = currentSize + bitNum - 32;
			temp = temp << (bitNum - offset);
			index++;
			tempRight = buf[index];
			tempRight = tempRight >> (32 - (bitNum - offset));
			ch = temp ^ tempRight;
			fprintf(outFile, "%c", ch);
		}
		else if (currentSize + bitNum == 32)
		{
			temp = buf[index];
			temp <<= currentSize;
			temp >>= currentSize;
			ch = temp;
			index++;
			currentSize = 0;
			fprintf(outFile, "%c", ch);
		}
		else 
		{
			temp = buf[index] << currentSize;
			ch = temp >> (32 - bitNum);
			currentSize += bitNum;
			fprintf(outFile, "%c", ch);
		}
	}
	return true;
}

