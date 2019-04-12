#pragma once

#include <QtWidgets/QWidget>
#include "ui_imgCompress.h"
#include <Windows.h>
#include <vector>
#include <QFile>
#include <QProgressBar>
#include <QFileDialog>
#include <QIODevice>
#include <QDebug>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QStyleFactory>
//sonWindow
#include "sonMain.h"
using namespace std;

class imgCompress : public QWidget
{
	Q_OBJECT


public:
	imgCompress(QWidget *parent = Q_NULLPTR);
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);


	void compressReadImag();
	void compress();

	void decompressReadImag();
	void decompress();

	//copress
	void getSegment(int n, vector<int> &segment, vector<int> &segmentBit);


	//new window
	void newMd5Window();
signals:
	void sendProgress(int);//ÏÔÊ¾½ø¶È
private:
	void putInt(unsigned int writeBuf[],unsigned int &index, unsigned int &currentSize,unsigned int num,unsigned int bitNum);
	bool putChar(unsigned int &index,unsigned int &currentSize, unsigned int &sum);
	Ui::imgCompressClass ui;
	QString filename;


	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	unsigned char *pallet;
	FILE *inFile;
	FILE *outFile;
	unsigned char *inData;
	unsigned int *buf;
	int fileSize;
	int rest;


	vector<int> segment;
	vector<int> segmentBit;
};
