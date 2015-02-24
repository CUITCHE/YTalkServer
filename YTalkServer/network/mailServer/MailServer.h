#ifndef MAILSERVER_H
#define MAILSERVER_H

#include <QObject>
class MailServer : public QObject
{
	Q_OBJECT

public:
	MailServer(QObject *parent);
	~MailServer();
	bool sendMail(const QString &sendTor, const QString &sendData);
protected slots:
	void onReadyRead();
protected:
	void whichDo(int step);
private:
	int sendStep;
};

#endif // MAILSERVER_H
