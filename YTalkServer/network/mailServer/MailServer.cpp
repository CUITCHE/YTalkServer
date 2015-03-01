#include "stdafx.h"
#include "MailServer.h"
#include <QHostInfo>
#include <QTcpSocket>
#include <QThread>
#define Quit 8

QMap<QTcpSocket*, MsgSend> MailServer::s_mails_list;
QString MailServer::username = "ytalkadmin";
QString MailServer::pw = "jieran753";
QString MailServer::smtpServer = "smtp.163.com";
QMutex* MailServer::mutex = new QMutex;
TimingThread* MailServer::thread_t_doing = nullptr;
class TimingThread: public QThread
{
protected:
	void run(){
		forever{
			QThread::msleep(5 * 1000);
			MailServer::timingCheck();
		}
	}
};
MailServer::MailServer(QObject *parent)
	: QObject(parent)
	, sendStep(-1)
{
	if (thread_t_doing == nullptr){
		thread_t_doing = new TimingThread;
		thread_t_doing->start();
	}
}

MailServer::~MailServer()
{

}
void MailServer::sendMail(const QString &sendTor, const QString &sendData)
{	
	static QHostInfo hostInfo = QHostInfo::fromName(smtpServer);
	QTcpSocket *sock = new QTcpSocket(this);
	{
		QMutexLocker locker(mutex);
		s_mails_list.insert(sock, { sock, sendTor, sendData });
	}
	sock->connectToHost(hostInfo.addresses().at(0), 25);
	connect(sock, &QTcpSocket::readyRead, this, &MailServer::onReadyRead);
/*
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(25);    //port of SMTP
	sin.sin_addr.S_un.S_addr = hostInfo.addresses().at(0).toIPv4Address();

	//connect to the mail server
	SOCKET s = socket(PF_INET, SOCK_STREAM, 0);
	if (::connect(s, (sockaddr*)&sin, sizeof(sin))) {
		qDebug() << "failed to connect the mail server";
		return false;
	}

	//
	char recvBuffer[1024];
	Recv(s, recvBuffer, sizeof(recvBuffer));    //wait for greeting message
	Send(s, QString("HELO ") + smtpServer + "\r\n");
	Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "250 OK"

	//start to log in    
	Send(s, QString("auth login\r\n"));
	Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "334 username:"(This is the decode message)

	Send(s, username.toLatin1().toBase64() + "\r\n");
	Recv(s, recvBuffer, sizeof(recvBuffer));
	if (QString(recvBuffer).mid(0, 3) != "334") {
		qDebug() << "username is error!";
		return false;
	}

	Send(s, pw.toLatin1().toBase64() + "\r\n");
	Recv(s, recvBuffer, sizeof(recvBuffer));
	if (QString(recvBuffer).mid(0, 3) != "235") {
		qDebug() << "password error";
		return false;
	}

	//Set sender
	Send(s, "mail from:<" + username + ">\r\n");
	Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "250 Mail OK"

	//set receiver
	Send(s, "rcpt to:<" + sendTor + ">\r\n");
	Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "250 Mail OK"

	//send data
	Send(s, QString("data\r\n"));
	Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "354 End data with <CR><LF>.<CR><LF>"
	Send(s, "to:" + sendTor + "\r\n" + "subject:the newest IP\r\n\r\n" + sendData + "\r\n.\r\n");
	Recv(s, recvBuffer, sizeof(recvBuffer));

	Send(s, QString("quit\r\n"));
	Recv(s, recvBuffer, sizeof(recvBuffer));
	closesocket(s);*/
}

void MailServer::onReadyRead()
{
	QTcpSocket *sock = qobject_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		return;
	}
	auto data = sock->readAll();
	whichDo(sendStep, sock);
}

void MailServer::whichDo(int step, QTcpSocket *sock)
{
	++sendStep;
	static const QByteArray hello = QByteArray("HELO ") + smtpServer.toLatin1() + "\r\n";
	static const QByteArray authLogin = "auth login\r\n";
	static const QByteArray userName = username.toLatin1().toBase64() + "\r\n";
	static const QByteArray password = pw.toLatin1().toBase64() + "\r\n";
	static const QByteArray mailFrom = "mail from:<" + username.toLatin1() + ">\r\n";
	static const QByteArray data = "data\r\n";
	QMap<QTcpSocket*, MsgSend>::iterator iter;
	switch (sendStep)
	{
	case 0:
		//得到邮件服务器的响应,连接到服务的时候
		sock->write(hello);
		break;
	case 1:
		//如果hello成功，将会发送登陆请求信息
		sock->write(authLogin);
		break;
	case 2:
		//登陆请求答应后，发送用户名，如果用户名错误将会导致错误
		sock->write(userName);
		break;
	case 3:
		//发送密码信息，如果密码错误，将会导致登陆失败
		sock->write(password);
		break;
	case 4:
		//发送发件人信息
		sock->write(mailFrom);
		break;
	case 5:
		//发送接收人信息
		iter = s_mails_list.find(sock);
		if (iter != s_mails_list.end()){
			sock->write("rcpt to:<" + iter->sendTor.toLatin1() + ">\r\n");
		}
		else{
			//结束此次邮件发送
		}
		break;
	case 6:
		//发送data请求
		sock->write(data);
		break;
	case 7:
		//发送正文信息
		iter = s_mails_list.find(sock);
		sock->write("to:" + iter->sendTor.toLatin1() + "\r\n"
			+ "subject:YTalk 用户注册验证\r\n\r\n" + iter->sendData.toLatin1() + "\r\n.\r\n");
		break;
	case Quit:
		//这里是退出邮件服务，可以考虑不退出，隔一段时间再退出
		sock->write("quit\r\n");
		break;
	}
}

void MailServer::timingCheck()
{
	QMutexLocker locker(mutex);
	static QMap<QTcpSocket*, MsgSend>::iterator iter_s, iter_e;
	iter_s = s_mails_list.begin();
	iter_e = s_mails_list.end();
	while (iter_s != iter_e){
		if (*iter_s){
			iter_s.key()->abort();
			iter_s.key()->deleteLater();
			iter_s = s_mails_list.erase(iter_s);
			continue;
		}
		++iter_s;
	}
}
