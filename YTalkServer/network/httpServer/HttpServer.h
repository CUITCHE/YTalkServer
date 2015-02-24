#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
class QTcpServer;
class QTcpSocket;
class HttpServer : public QObject
{
	Q_OBJECT

public:
	HttpServer(QObject *parent = 0);
	~HttpServer();
protected:
	void mailAddressValidate(QTcpSocket *sock, const QStringList &html);
	void _404(QTcpSocket *sock);
protected slots:
	void onNewConnection();
	void onReadyRead();
	void onSocketDisconnected();
private:
	QTcpServer *m_listeningSocket;
};

#endif // HTTPSERVER_H
