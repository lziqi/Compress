#include "sonMain.h"

sonMain::sonMain(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAcceptDrops(true);
	ui.aFilename->setEnabled(false);
	ui.bFilename->setEnabled(false);
	ui.aMD5->setEnabled(false);
	ui.bMD5->setEnabled(false);
}

sonMain::~sonMain()
{
}

void sonMain::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void sonMain::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;
	QString filename = urls.first().toLocalFile();
	if (ui.aFilename->text().isEmpty())
	{
		ui.aFilename->setText(filename);
	}
	else 
	{
		ui.bFilename->setText(filename);
	}
	

	if (!ui.aFilename->text().isEmpty() && !ui.bFilename->text().isEmpty())
	{
		QFile a(ui.aFilename->text());
		QFile b(ui.bFilename->text());
		a.open(QIODevice::ReadOnly);
		b.open(QIODevice::ReadOnly);
		QByteArray ba = QCryptographicHash::hash(a.readAll(), QCryptographicHash::Md5);
		ui.aMD5->setText(ba.toHex().constData());
		ba = QCryptographicHash::hash(b.readAll(), QCryptographicHash::Md5);
		ui.bMD5->setText(ba.toHex().constData());
		a.close();
		b.close();
	}
}
