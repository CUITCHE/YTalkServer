#include "MailServer.h"
#include "SettingHelper.h"
#include <QHostInfo>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#define Quit 8

//facade of function send()
void Send(int& s, const QByteArray& data) {
	if (send(s, data, data.length(), 0) == SOCKET_ERROR) {
		qDebug() << "send data \"" << data << "\" error";
	}
}

//facade of function recv()
void Recv(int& s, char* buf, int len) {
	memset(buf, 0, len);
	if (recv(s, buf, len, 0) == SOCKET_ERROR) {
		qDebug() << "error, while receiving data";
	}
}

MailServer::MailServer(QObject *parent)
	: QThread(parent)
	, waitToSendList(new QList<MsgSend>)
	, username(new QString)
	, password(new QString)
	, smtpServerAddress(new QString)
	, mutex(new QMutex)
{

}

MailServer::~MailServer()
{
	delete waitToSendList;
	delete username;
	delete password;
	delete smtpServerAddress;
	delete mutex;
}
void MailServer::sendMail(const QByteArray &sendTor, const QByteArray &sendData)
{
	mutex->lock();
	waitToSendList->push_back({ sendTor, sendData });
	mutex->unlock();
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
	Send(s, QString("HELO ") + smtpServerAddress + "\r\n");
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

	Send(s, password.toLatin1().toBase64() + "\r\n");
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



void MailServer::run()
{
	MsgSend tmp;
	forever{
		if (waitToSendList->isEmpty() == true){
			QThread::msleep(1);
			continue;
		}
		if (netCheck() == false && connectToMailServer() == false){
			QThread::msleep(1);
			continue;
		}
		
		mutex->lock();
		tmp = waitToSendList->takeFirst();
		send_impl(tmp);
		mutex->unlock();
		//每发送一封休息一会儿
		QThread::msleep(1);
	}
}

bool MailServer::connectToMailServer()
{
	static const QByteArray hello = QByteArray("HELO ") + smtpServerAddress->toLatin1() + "\r\n";
	static const QByteArray authLogin = "auth login\r\n";
	static const QByteArray userName = username->toLatin1().toBase64() + "\r\n";
	static const QByteArray password1 = password->toLatin1().toBase64() + "\r\n";
	

	try{
		sockaddr_in addr_in;
		memset(&addr_in, 0, sizeof(addr_in));
		addr_in.sin_family = AF_INET;
		addr_in.sin_port = htons(25);    //port of SMTP
		auto ins = get<SettingHelper>();
		QHostInfo ph = QHostInfo::fromName(ins->getValue("mailServerAddress").toString());
		ULONG address = ph.addresses().at(0).toIPv4Address();
		memcpy(&addr_in.sin_addr.S_un.S_addr, &address, sizeof(address));

		//connect to the mail server
		smptSocket = ::socket(AF_INET, SOCK_STREAM, 0);
		if (::connect(smptSocket, (sockaddr*)&addr_in, sizeof(addr_in))) {
			qDebug() << "failed to connect the mail server";
			return false;
		}
		char recvBuffer[1024];
		Recv(smptSocket, recvBuffer, sizeof(recvBuffer));    //wait for greeting message
		Send(smptSocket, "HELO " + smtpServerAddress->toLatin1() + "\r\n");
		Recv(smptSocket, recvBuffer, sizeof(recvBuffer));    //should recv "250 OK"

		//start to log in    
		Send(smptSocket, "auth login\r\n");
		Recv(smptSocket, recvBuffer, sizeof(recvBuffer));    //should recv "334 username:"(This is the decode message)

		Send(smptSocket, userName);
		Recv(smptSocket, recvBuffer, sizeof(recvBuffer));
		if (!(recvBuffer[0] == '3' && recvBuffer[1] == '3' && recvBuffer[2] == '4')){
			qDebug() << "username is error!";
			return false;
		}

		Send(smptSocket, password1);
		Recv(smptSocket, recvBuffer, sizeof(recvBuffer));
		if (!(recvBuffer[0] == '2' && recvBuffer[1] == '3' && recvBuffer[2] == '5')) {
			qDebug() << "password error";
			return false;
		}
	}
	catch (...){
		qDebug() << __FUNCSIG__ << "函数中，出现了意外失败";
	}
	//至此登陆完毕
	return true;
}

void MailServer::send_impl(const MsgSend &msg)
{
	static const QByteArray mailFrom = "mail from:<" + username->toLatin1() + ">\r\n";
	static const QByteArray data = "data\r\n";
	static const QString subject = SettingHelper::instance()->getValue("mailServerSubject").toString();
	static const QString serverPort = SettingHelper::instance()->getValue("httpServerPort").toString();
	static const QString serverIp = SettingHelper::instance()->getValue("httpServerIp").toString();
	static const QString httpServerUrl = QString("http://") + serverIp + QString(":") + (serverPort)+SettingHelper::instance()->getValue("httpServerTail").toString();
	static char recvBuffer[1024];

	QString mailServerContent = SettingHelper::instance()->getValue("mailServerContent").toString().toLatin1();
	//Set sender
	Send(smptSocket, mailFrom);
	Recv(smptSocket, recvBuffer, sizeof(recvBuffer));    //should recv "250 Mail OK"

	//set receiver
	Send(smptSocket, "rcpt to:<" + msg.sendTor + ">\r\n");
	Recv(smptSocket, recvBuffer, sizeof(recvBuffer));    //should recv "250 Mail OK"

	//send data
	Send(smptSocket, data);
	Recv(smptSocket, recvBuffer, sizeof(recvBuffer));    //should recv "354 End data with <CR><LF>.<CR><LF>"

	QString sendFinalData = "to:" + msg.sendTor + "\r\n" + QString("subject:%1\r\n\r\n").arg(subject) + 
		mailServerContent.arg(QString(msg.sendTor)).arg(httpServerUrl).arg(QString(msg.sendData)) + "\r\n.\r\n";
	Send(smptSocket, sendFinalData.toLatin1());
	Recv(smptSocket, recvBuffer, sizeof(recvBuffer));

	//一份邮件发送完毕
}

bool MailServer::netCheck()
{
	int ret = ::send(smptSocket, nullptr, 0, 0);
	return ret != -1;
}
