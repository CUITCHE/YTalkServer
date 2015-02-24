#include "stdafx.h"
#include "MailServer.h"
#include <QHostInfo>
#include <QTcpSocket>
MailServer::MailServer(QObject *parent)
	: QObject(parent)
	, sendStep(-1)
{

}

MailServer::~MailServer()
{

}
//facade of function send()
void Send(SOCKET& s, const QString& data) {
	if (send(s, data.toLatin1(), data.length(), 0) == SOCKET_ERROR) {
		qDebug() << "send data \"" << data << "\" error";
	}
}

//facade of function recv()
void Recv(SOCKET& s, char* buf, int len) {
	memset(buf, 0, len);
	if (recv(s, buf, len, 0) == SOCKET_ERROR) {
		qDebug() << "error, while receiving data";
	}
}
bool MailServer::sendMail(const QString &sendTor, const QString &sendData)
{
	QString smtpServer = "smtp.163.com";
	QString username = "ytalkadmin";
	QString pw = "jieran753";
	QHostInfo hostInfo = QHostInfo::fromName(smtpServer);
	QTcpSocket *sock = new QTcpSocket(this);
	sock->connectToHost(hostInfo.addresses().at(0), 25);
	connect(sock, &QTcpSocket::readyRead, this, &MailServer::onReadyRead);
// 	sockaddr_in sin;
// 	memset(&sin, 0, sizeof(sin));
// 	sin.sin_family = AF_INET;
// 	sin.sin_port = htons(25);    //port of SMTP
// 	sin.sin_addr.S_un.S_addr = hostInfo.addresses().at(0).toIPv4Address();
// 
// 	//connect to the mail server
// 	SOCKET s = socket(PF_INET, SOCK_STREAM, 0);
// 	if (::connect(s, (sockaddr*)&sin, sizeof(sin))) {
// 		qDebug() << "failed to connect the mail server";
// 		return false;
// 	}

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
	closesocket(s);
	return true;
}

void MailServer::onReadyRead()
{
	QTcpSocket *sock = qobject_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		return;
	}
	auto data = sock->readAll();
	if (data.contains("220")){

	}
}

void MailServer::whichDo(int step)
{
	++sendStep;
	switch (sendStep)
	{
	case 0:
		//得到邮件服务器的响应

		break;
	case 1:
		break;
	}
}
