#ifndef MAILSERVER_H
#define MAILSERVER_H

#include <QThread>
#include <QList>
class QTimer;
class QMutex;

struct MsgSend{
	//operator bool(){ return hasSend; }
	//quint32 hasSend;		//0����û�з�����ɣ�1:�����Ѿ��������
	QByteArray sendTor;		//�ռ�����Ϣ
	QByteArray sendData;		//����������
};

class MailServer : public QThread
{
public:
	MailServer(QObject *parent = 0);
	~MailServer();
	//ֻ�Ѵ��������ռ�����Ϣ��Ҫ���͵����ݱ�����
	//�������б��в����أ��ʶ�����ʵʱ�ķ����ʼ���һ���ӳ���3-5���ӣ�������ٵ�����£�
	void sendMail(const QByteArray &sendTor, const QByteArray &sendData);

protected:
	//���߳���ִ���ʼ�����
	void run();
	//connect emai server
	bool connectToMailServer();
	//�����ʼ����ͳ���
	void send_impl(const MsgSend &msg);
	//������
	bool netCheck();
private:
	QList<MsgSend> *waitToSendList;	//�������б�
	int smptSocket;	//�ʼ�socket
	QString *username;		//�ʼ�������ʺ�
	QString *password;		//�ʼ��ʺŵ����루���ģ�
	QString *smtpServerAddress;	//�ʼ�����ĵ�ַ
	QMutex *mutex;
};

#endif // MAILSERVER_H
