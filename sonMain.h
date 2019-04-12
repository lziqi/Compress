#pragma once

#include <QWidget>
#include "ui_sonMain.h"
#include <QList>
#include <QFile>
#include <QCryptographicHash>
#include <QDragEnterEvent>
#include <QMimeData>
class sonMain : public QWidget
{
	Q_OBJECT
public:
	sonMain(QWidget *parent = Q_NULLPTR);
	~sonMain();

	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
private:
	Ui::sonMain ui;
};
