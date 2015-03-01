#ifndef MAILSERVER_H
#define MAILSERVER_H

#include <QObject>
#include <QMap>
class QTcpSocket;
class QTimer;
class QMutex;

struct MsgSend{
	operator bool(){ return hasSend; }
	QTcpSocket *sock;
	QString sendTor;
	QString sendData;
	int hasSend;		//0：还没有发送完成，否则则是已经发送完成
};

class MailServer : public QObject
{
	Q_OBJECT
	friend class TimingThread;
public:
	MailServer(QObject *parent);
	~MailServer();
	void sendMail(const QString &sendTor, const QString &sendData);
protected slots:
	void onReadyRead();
protected:
	void whichDo(int step, QTcpSocket *sock);
	static void timingCheck();
private:
	int sendStep;
	static QMap<QTcpSocket*, MsgSend> s_mails_list;
	static QString username;
	static QString pw;
	static QString smtpServer;
	static QMutex *mutex;
	static TimingThread *thread_t_doing;
};

#endif // MAILSERVER_H
