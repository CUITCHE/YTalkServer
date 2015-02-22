#ifndef NETLOGICMAINPROCESS_H
#define NETLOGICMAINPROCESS_H
/********************************************************************
	created:	2015/02/22
	created:	22:2:2015   13:22
	file base:	NetLogicMainProcess
	author:		CHE
	
	purpose:	网络通信处理模块
				处理客户端与服务端的通信逻辑，
				调用数据库接口，处理服务端与数据库
				[关于结束本类，建议直接使用delete操作]
*********************************************************************/
#include <QThread>
class NetServerControl;
struct NetCommunicationModule;
class NetLogicMainProcess : public QThread
{
	Q_OBJECT

public:
	NetLogicMainProcess(QObject *parent = 0);

	//如果处理线程，还未结束，将会等待2s，之后若还未结束就强制结束
	~NetLogicMainProcess();

	//使active=true，然后调用QThread的start
	void start();

	//将active=false，在上层调用wait函数，等待线程退出。之后可强制退出，调用terminate
	void stop();

	//返回网络通信处理模块的活动状态，return true if it is active;
	bool isActive()const;
protected:
	void run();
	void task(const NetCommunicationModule &NCM);
private:
	bool active;	//true，run() is runing,;false run() will be ending.
	bool permit;	//
	NetServerControl *m_socket;
};

#endif // NETLOGICMAINPROCESS_H
