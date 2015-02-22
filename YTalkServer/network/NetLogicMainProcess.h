#ifndef NETLOGICMAINPROCESS_H
#define NETLOGICMAINPROCESS_H
/********************************************************************
	created:	2015/02/22
	created:	22:2:2015   13:22
	file base:	NetLogicMainProcess
	author:		CHE
	
	purpose:	����ͨ�Ŵ���ģ��
				����ͻ��������˵�ͨ���߼���
				�������ݿ�ӿڣ��������������ݿ�
				[���ڽ������࣬����ֱ��ʹ��delete����]
*********************************************************************/
#include <QThread>
class NetServerControl;
struct NetCommunicationModule;
class NetLogicMainProcess : public QThread
{
	Q_OBJECT

public:
	NetLogicMainProcess(QObject *parent = 0);

	//��������̣߳���δ����������ȴ�2s��֮������δ������ǿ�ƽ���
	~NetLogicMainProcess();

	//ʹactive=true��Ȼ�����QThread��start
	void start();

	//��active=false�����ϲ����wait�������ȴ��߳��˳���֮���ǿ���˳�������terminate
	void stop();

	//��������ͨ�Ŵ���ģ��Ļ״̬��return true if it is active;
	bool isActive()const;
protected:
	void run();
	void task(const NetCommunicationModule &NCM);
private:
	bool active;	//true��run() is runing,;false run() will be ending.
	bool permit;	//
	NetServerControl *m_socket;
};

#endif // NETLOGICMAINPROCESS_H
