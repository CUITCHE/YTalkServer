#ifndef NETSERVERCONTROL_H
#define NETSERVERCONTROL_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   20:29
	file base:	NetServerControl
	author:		CHE
	
	purpose:	��������ͨ�ţ�
				��ʱ��Qt��װ���������������
				֮���������ٸ���������Чģʽ��
				�����п��ܲ���QQ��UDP+TCP�Ļ��
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
	//���ͻ�������Ϣʱ�����ʹ��ź�
	void datagram(QTcpSocket*, const QByteArray &);
public slots:
	//�пͻ�������
	void newConnectionProcess();
	//�ͻ�������Ϣ���͹���
	void pendingRecieveData();
private:
	unique_ptr<QTcpServer> serverSocket;		//����socket
	QList<shared_ptr<QTcpSocket>> connections;		//�洢�������ӵ�socket,key=ip��ַ��int��
};

#endif // NETSERVERCONTROL_H
