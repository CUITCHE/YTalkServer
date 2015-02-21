#include "stdafx.h"
#include "NetServerControl.h"
#include <QTcpSocket>
NetServerControl::NetServerControl(QObject *parent)
	: QObject(parent)
	, serverSocket(new QTcpServer(this))
{
	doListen();
}

NetServerControl::~NetServerControl()
{

}

void NetServerControl::newConnectionProcess()
{
	QTcpSocket *sock = serverSocket->nextPendingConnection();
	connect(sock, &QTcpSocket::readyRead, this, &NetServerControl::pendingRecieveData);
	int ip = sock->localAddress().toIPv4Address();
	connections.push_back(shared_ptr<QTcpSocket>(sock));
}

void NetServerControl::doListen()
{
	GET_INSTANCE(SettingHelper);
	auto ip = ins->getValue("serverIp").toString();
	auto port = ins->getValue("serverPort").toInt();
	bool ret = serverSocket->listen(QHostAddress(ip),port);
	if (ret == false){
		qDebug() << "����ʧ��";
		__debugbreak();
	}
	connect(serverSocket.get(), &QTcpServer::newConnection, this, &NetServerControl::newConnectionProcess);
}

void NetServerControl::pendingRecieveData()
{
	QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		qDebug() << "���մ����tcp socket sender";
		__debugbreak();
		return;
	}
	auto data = sock->readAll();
	//�׳����ݣ������ݴ�����ȥ����
	emit datagram(sock, data);
}
