#ifndef TRANSACTION_H
#define TRANSACTION_H
/********************************************************************
	created:	2015/03/19
	created:	19:3:2015   11:51
	file base:	Transaction
	author:		CHE
	
	purpose:	事务处理类
				调用数据库接口，处理服务端与数据库
				处理服务端与客户端的事务逻辑交互。【implement】
*********************************************************************/
#include <QObject>
class Packet;
class QMutex;
class QTcpSocket;
class NetLogicMainProcess;
class Transaction : public QObject
{
	Q_OBJECT

public:
	Transaction(NetLogicMainProcess *parent);
	~Transaction();

	//************************************
	// Method:    lock
	// FullName:  Transaction::lock
	// Access:    public 
	// Returns:   void
	// Qualifier: 传入需要处理的Packet指针，进入事务流程，并对事务进行上锁
	// Parameter: Packet * pct 为下一个事务准备请求包内容
	// Parameter: QTcpSocket * sock 来自sock，请求了服务。
	//************************************
	void lock(Packet *pct, QTcpSocket *sock);

	//************************************
	// Method:    unlock
	// FullName:  Transaction::unlock
	// Access:    public 
	// Returns:   void
	// Qualifier: 解锁事务，可以进行下一个事务
	//************************************
	void unlock();

	//************************************
	// Method:    userLogin
	// FullName:  Transaction::userLogin
	// Access:    public 
	// Returns:   bool 总是返回true
	// Qualifier: 用户登陆逻辑处理
	//************************************
	bool userLogin();
private:
	Packet *preparePacket;		//临时包
	QTcpSocket *remoteSocket;	//临时远程socket套接字
	const NetLogicMainProcess *netLogicMainProcess;
	QMutex *prepareMutex;
};

#endif // TRANSACTION_H
