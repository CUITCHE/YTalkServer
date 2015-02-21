#ifndef SETTINGINFO_H
#define SETTINGINFO_H

#include "AbstractParseJson.h"

class SettingInfo : public AbstractParseJson
{
	Q_OBJECT
	//���ݿ�����
	QT_MOC_MINE_DEFINITION(QString, DBServerName, DBServerName);
	QT_MOC_MINE_DEFINITION(QString, DBServerPort, DBServerPort);
	QT_MOC_MINE_DEFINITION(QString, DBDatabaseName, DBDatabaseName);
	QT_MOC_MINE_DEFINITION(QString, DBUserName, DBUserName);
	QT_MOC_MINE_DEFINITION(QString, DBPassword, DBPassword);
	//������ip��ַ�Ͷ˿�����
	QT_MOC_MINE_DEFINITION(QString, serverIp, ServerIp);
	QT_MOC_MINE_DEFINITION(int, serverPort, ServerPort);
};

#endif // SETTINGINFO_H
