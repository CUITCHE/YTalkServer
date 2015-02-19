#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qDebug() << "nihÄãºÃ";
	printf("nihÄãºÃ");
	return a.exec();
}
