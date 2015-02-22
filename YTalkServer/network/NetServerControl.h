#ifndef NETSERVERCONTROL_H
#define NETSERVERCONTROL_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   20:29
	file base:	NetServerControl
	author:		CHE
	
	purpose:	网络通信接收模块，
				暂时用Qt封装的网络库来操作，
				之后有需求再改用其它高效模式，
				甚至有可能采用QQ的UDP+TCP的混搭
*********************************************************************/
#include <QList>
#include <QQueue>
#include <memory>
using namespace std;
class QTcpServer;
class QTcpSocket;
class QMutex;
//客户端与服务端交互所需要的数据结构
struct NetCommunicationModule
{
	QTcpSocket *sock;
	QByteArray data;
};
class NetServerControl : public QObject
{
	Q_OBJECT

public:
	NetServerControl(QObject *parent = 0);
	~NetServerControl();

	//移出指定的socket
	void removeSocket(QTcpSocket *sock);

	//判断是否有数据到来
	bool isPendingClientData()const;

	//从sharedDataList取出一条数据
	NetCommunicationModule getPendingData();
protected:
	void doListen();
public slots:
	//有客户端连入
	void newConnectionProcess();

	//客户端有消息发送过来
	void pendingRecieveData();

	//客户端与服务端断开连接的处理
	void onClientSocketDisconnect();
private:
	QTcpServer *serverSocket;		//监听socket
	QList<shared_ptr<QTcpSocket>> connections;		//存储所有连接的socket
	QMutex *mutex;									//sharedDataList的互斥锁
	QList<NetCommunicationModule> sharedDataList;	//客户端发来的数据，存储了是谁发来的QTcpSocket指针
};

#endif // NETSERVERCONTROL_H
