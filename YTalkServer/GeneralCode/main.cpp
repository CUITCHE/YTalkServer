#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "SettingHelper.h"
#include "test/TestPacket.hpp"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TestPacket *test = new TestPacket();
	test->setName("һ������");
	test->setCount(123);
	test->setPassword("�����߰�");
	auto data = test->read();
	qDebug() << data;
	return a.exec();
}
