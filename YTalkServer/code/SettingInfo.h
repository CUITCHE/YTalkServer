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
};

#endif // SETTINGINFO_H
