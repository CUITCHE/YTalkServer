#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "DBModule.h"
#include "httpServer/HttpServer.h"
#include "ServerBackPacket.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ServerBackPacket *pck = new ServerBackPacket;
	pck->setOperator(23);
	pck->setReason("214324325345");
	pck->setResult(9);
	auto data = QJsonDocument::fromVariant(pck->read()).toJson();
	qDebug() << data;
	return a.exec();
}
