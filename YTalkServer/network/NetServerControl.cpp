#include "stdafx.h"
#include "NetServerControl.h"
#include <QTcpSocket>
#include <algorithm>
#include <QMutex>
#include <QTcpServer>
using namespace std;
NetServerControl::NetServerControl(QObject *parent)
	: QObject(parent)
	, serverSocket(new QTcpServer(this))
	, mutex(new QMutex)
{
	doListen();
}

NetServerControl::~NetServerControl()
{
	delete mutex;
}

void NetServerControl::newConnectionProcess()
{
	QTcpSocket *sock = serverSocket->nextPendingConnection();
	connect(sock, &QTcpSocket::readyRead, this, &NetServerControl::pendingRecieveData);
	connect(sock, &QAbstractSocket::disconnected, this, &NetServerControl::onClientSocketDisconnect);
	
	connections.push_back(shared_ptr<QTcpSocket>(sock));
}

void NetServerControl::doListen()
{
	auto ins = get<SettingHelper>();
	auto ip = ins->getValue("serverIp").toString();
	auto port = ins->getValue("serverPort").toInt();
	bool ret = serverSocket->listen(QHostAddress(ip),port);
	if (ret == false){
		qDebug() << "����ʧ��";
		__debugbreak();
	}
	connect(serverSocket, &QTcpServer::newConnection, this, &NetServerControl::newConnectionProcess);
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
	//�洢���ݵ�sharedDataList�������ݴ�����ȥ����
	QMutexLocker locker(mutex);
	sharedDataList.push_back({ sock, data });
}

void NetServerControl::removeSocket(QTcpSocket *sock)
{
	//��������shared_ptr(_Ptr)ȥ����һ��shared_ptr�����ܻ����й©��
	//�Լ����delete
	auto ret = std::remove_if(connections.begin(), connections.end(),
		[=](const shared_ptr<QTcpSocket> &val){return val.get() == sock; });
	if (ret != connections.end()){
		connections.erase(ret);
	}
}

void NetServerControl::onClientSocketDisconnect()
{
	QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		qDebug() << "���մ����tcp socket sender";
		__debugbreak();
		return;
	}
	this->removeSocket(sock);
	sock->deleteLater();
}

bool NetServerControl::isPendingClientData() const
{
	return !sharedDataList.isEmpty();
}

NetCommunicationModule NetServerControl::getPendingData()
{
	QMutexLocker locker(mutex);
	return sharedDataList.takeFirst();
}