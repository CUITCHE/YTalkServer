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
		qDebug() << "http服务 监听失败";
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
	//获得两段参数
	if (params.size() == 2){
		try{
			QString email = params.at(0).split('=').at(1);
			QString validateCode = params.at(1).split('=').at(1);
			if (validateCode.size() != 20){
				throw "";
			}
			GET_INSTANCE(DBModule);
	
			QString retinfo = QString("<h1>邮箱地址：");
			retinfo.append(email).append("  注册");
			if (ins->accountValidate(email, validateCode)){
				retinfo.append("成功</h1>");
			}
			else{
				retinfo.append("失败</h1>");
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
		qDebug() << __FUNCSIG__ << "空的socket";
		return;
	}
	QByteArray data = sock->readAll();
	QString info(data);
	//获取每一行信息
	QStringList tokens(info.split("\r\n"));
	if (tokens.size() > 0 && tokens.at(0).contains("GET")){
		//得到中间的参数段
		QStringList temp = tokens.at(0).split(" ");
		if (temp.size() >= 2){
			//得到参数xxx?123=4232&3213=432
			QStringList params = temp.at(1).split("?");
			//判断是否是一个合法的url的参数
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
		qDebug() << __FUNCSIG__ << "空的socket";
		return;
	}
	sock->deleteLater();
}
