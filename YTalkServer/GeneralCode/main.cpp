#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qDebug() << "nih���";
	printf("nih���");
	return a.exec();
}
