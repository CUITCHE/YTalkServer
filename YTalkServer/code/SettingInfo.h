#ifndef SETTINGINFO_H
#define SETTINGINFO_H

#include "AbstractParseJson.h"

class SettingInfo : public AbstractParseJson
{
	Q_OBJECT
	//数据库配置
	QT_MOC_MINE_DEFINITION(QString, DBServerName, DBServerName);
	QT_MOC_MINE_DEFINITION(QString, DBServerPort, DBServerPort);
	QT_MOC_MINE_DEFINITION(QString, DBDatabaseName, DBDatabaseName);
	QT_MOC_MINE_DEFINITION(QString, DBUserName, DBUserName);
	QT_MOC_MINE_DEFINITION(QString, DBPassword, DBPassword);
	//服务器ip地址和端口配置
	QT_MOC_MINE_DEFINITION(QString, serverIp, ServerIp);
	QT_MOC_MINE_DEFINITION(int, serverPort, ServerPort);
	//http用于邮箱验证的http服务器
	QT_MOC_MINE_DEFINITION(QString, httpServerIp, HttpServerIp);
	QT_MOC_MINE_DEFINITION(int, httpServerPort, HttpServerPort);
	QT_MOC_MINE_DEFINITION(QString, httpServerTail, HttpServerTail);
	//邮件服务器配置
	QT_MOC_MINE_DEFINITION(QString, mailServerAddress, MailServerAddress);
	QT_MOC_MINE_DEFINITION(QString, mailServerUsrName, MailServerUsrName);
	QT_MOC_MINE_DEFINITION(QString, mailServerUsrPassword, MailServerUsrPassword);
	QT_MOC_MINE_DEFINITION(QString, mailServerSubject, MailServerSubject);
	QT_MOC_MINE_DEFINITION(QString, mailServerContent, MailServerContent);
};

#endif // SETTINGINFO_H
