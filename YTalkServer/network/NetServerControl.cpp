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
		qDebug() << "监听失败";
		__debugbreak();
	}
	connect(serverSocket, &QTcpServer::newConnection, this, &NetServerControl::newConnectionProcess);
}

void NetServerControl::pendingRecieveData()
{
	QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		qDebug() << "接收错误的tcp socket sender";
		__debugbreak();
		return;
	}
	auto data = sock->readAll();
	//存储数据到sharedDataList，给数据处理类去处理
	QMutexLocker locker(mutex);
	sharedDataList.push_back({ sock, data });
}

void NetServerControl::removeSocket(QTcpSocket *sock)
{
	//不可轻易shared_ptr(_Ptr)去构造一个shared_ptr，可能会造成泄漏，
	//以及多次delete
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
		qDebug() << "接收错误的tcp socket sender";
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
