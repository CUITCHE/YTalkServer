#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "SettingHelper.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SettingHelper::setValue("serverName", "≤‚ ‘");
	SettingHelper::sync();
	return a.exec();
}
