#include "imgCompress.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	imgCompress w;

	QApplication::setStyle(QStyleFactory::create("fusion"));
	w.setWindowTitle(QStringLiteral("Ñ¹ËõÈí¼þ"));

	w.show();
	return a.exec();
}
