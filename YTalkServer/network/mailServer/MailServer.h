#ifndef MAILSERVER_H
#define MAILSERVER_H

#include <QThread>
#include <QList>
class QTimer;
class QMutex;

struct MsgSend{
	//operator bool(){ return hasSend; }
	//quint32 hasSend;		//0：还没有发送完成；1:则是已经发送完成
	QByteArray sendTor;		//收件人信息
	QByteArray sendData;		//待发送数据
};

class MailServer : public QThread
{
public:
	MailServer(QObject *parent = 0);
	~MailServer();
	//只把传进来的收件人信息和要发送的数据保留在
	//带发送列表中并返回，故而不能实时的发送邮件，一般延迟在3-5分钟（请求较少的情况下）
	void sendMail(const QByteArray &sendTor, const QByteArray &sendData);

protected:
	//在线程中执行邮件服务
	void run();
	//connect emai server
	bool connectToMailServer();
	//启动邮件发送程序
	void send_impl(const MsgSend &msg);
	//网络检测
	bool netCheck();
private:
	QList<MsgSend> *waitToSendList;	//待发送列表
	int smptSocket;	//邮件socket
	QString *username;		//邮件服务的帐号
	QString *password;		//邮件帐号的密码（明文）
	QString *smtpServerAddress;	//邮件服务的地址
	QMutex *mutex;
};

#endif // MAILSERVER_H
