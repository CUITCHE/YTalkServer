#include "stdafx.h"
#include "HttpServer.h"
#include "DBModule.h"
#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
HttpServer::HttpServer(QObject *parent)
	: QObject(parent)
	, m_listeningSocket(new QTcpServer(this))
{
	GET_INSTANCE(SettingHelper);
	auto ip = ins->getValue("httpServerIp").toString();
	auto port = ins->getValue("httpServerPort").toInt();
	auto ret = m_listeningSocket->listen(QHostAddress(ip), port);
	if (ret == false){
		qDebug() << "http���� ����ʧ��";
		__debugbreak();
	}
	connect(m_listeningSocket, &QTcpServer::newConnection, this, &HttpServer::onNewConnection);
}

HttpServer::~HttpServer()
{

}

void HttpServer::onNewConnection()
{
	QTcpSocket *sock = m_listeningSocket->nextPendingConnection();
	connect(sock, &QTcpSocket::readyRead, this, &HttpServer::onReadyRead);
	connect(sock, &QTcpSocket::disconnected, this, &HttpServer::onSocketDisconnected);
}

void HttpServer::mailAddressValidate(QTcpSocket *sock, const QStringList &params)
{
	//������β���
	if (params.size() == 2){
		try{
			QString email = params.at(0).split('=').at(1);
			QString validateCode = params.at(1).split('=').at(1);
			if (validateCode.size() != 20){
				throw "";
			}
			GET_INSTANCE(DBModule);
	
			QString retinfo = QString("<h1>�����ַ��");
			retinfo.append(email).append("  ע��");
			if (ins->accountValidate(email, validateCode)){
				retinfo.append("�ɹ�</h1>");
			}
			else{
				retinfo.append("ʧ��</h1>");
			}
			QTextStream os(sock);
			os << retinfo;
			sock->close();
			return;
		}
		catch (...){
			goto label;
		}
	}
label:
	this->_404(sock);
}

void HttpServer::_404(QTcpSocket *sock)
{
	QTextStream test(sock);
	test << "<h1><center>404 Not Found!</center></h1>";
	sock->close();
}

void HttpServer::onReadyRead()
{
	auto sock = qobject_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		qDebug() << __FUNCSIG__ << "�յ�socket";
		return;
	}
	QByteArray data = sock->readAll();
	QString info(data);
	//��ȡÿһ����Ϣ
	QStringList tokens(info.split("\r\n"));
	if (tokens.size() > 0 && tokens.at(0).contains("GET")){
		//�õ��м�Ĳ�����
		QStringList temp = tokens.at(0).split(" ");
		if (temp.size() >= 2){
			//�õ�����xxx?123=4232&3213=432
			QStringList params = temp.at(1).split("?");
			//�ж��Ƿ���һ���Ϸ���url�Ĳ���
			if (params.size() == 2){
				this->mailAddressValidate(sock, params.at(1).split("&"));
				return;
			}
		}
	}
	this->_404(sock);
}

void HttpServer::onSocketDisconnected()
{
	auto sock = qobject_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		qDebug() << __FUNCSIG__ << "�յ�socket";
		return;
	}
	sock->deleteLater();
}
