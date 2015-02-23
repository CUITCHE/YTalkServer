#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "DBModule.h"
using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GET_INSTANCE(DBModule);
	ins->initConnect();
	ins->testQuery();
	return a.exec();
}
