#ifndef NETSERVERCONTROL_H
#define NETSERVERCONTROL_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   20:29
	file base:	NetServerControl
	author:		CHE
	
	purpose:	管理网络通信，
				暂时用Qt封装的网络库来操作，
				之后有需求再改用其它高效模式，
				甚至有可能采用QQ的UDP+TCP的混搭
*********************************************************************/
#include <QTcpServer>
#include <QList>
#include <QQueue>
#include <memory>
using namespace std;
class QTcpSocket;
class NetServerControl : public QObject
{
	Q_OBJECT

public:
	NetServerControl(QObject *parent = 0);
	~NetServerControl();
protected:
	void doListen();
signals:
	//当客户端来消息时，发送此信号
	void datagram(QTcpSocket*, const QByteArray &);
public slots:
	//有客户端连入
	void newConnectionProcess();
	//客户端有消息发送过来
	void pendingRecieveData();
private:
	unique_ptr<QTcpServer> serverSocket;		//监听socket
	QList<shared_ptr<QTcpSocket>> connections;		//存储所有连接的socket,key=ip地址的int码
};

#endif // NETSERVERCONTROL_H
