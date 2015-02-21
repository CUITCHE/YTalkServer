#include "stdafx.h"
#include "DBModule.h"
#include "SettingHelper.h"
PREPARE_INSTANCE_DEFINITION(DBModule);

DBModule::DBModule(QObject *parent)
	:QThread(parent)
{
}

DBModule::~DBModule()
{

}

void DBModule::initConnect()
{
	//从配置文件中读取数据库的相关信息
	GET_INSTANCE(SettingHelper);
	databaseInfo.serverName = ins->getValue("serverName").toString();
	databaseInfo.serverPort = ins->getValue("serverPort").toString();
	databaseInfo.databaseName = ins->getValue("databaseName").toString();
	databaseInfo.userName = ins->getValue("userName").toString();
	databaseInfo.password = ins->getValue("password").toString();
	QSqlError::ErrorType errorType;
	qDebug() << "****************数据库服务模块初始化****************";
	qDebug() << "默认配置:";
	qDebug() << "数据库服务器地址:" << databaseInfo.serverName;
	qDebug() << "数据库服务器端口:" << databaseInfo.serverPort;
	qDebug() << "数据库名称:" << databaseInfo.databaseName;
	qDebug() << "数据库用户名:" << databaseInfo.userName;
	qDebug() << "数据库密码:" << databaseInfo.password;
	int trycount = -1;
	do 
	{
		++trycount;
		errorType = MSSQLConnectionHelper::initConnection(databaseInfo);
		if (trycount > 0){
			qDebug() << "连接数据库失败" << trycount << "次，5秒后尝试重新连接......";
			QThread::msleep(5 * 1000);
		}
	} while (errorType != QSqlError::NoError);
	qDebug() << "数据库连接成功!";
}

void DBModule::disconnect()
{
	MSSQLConnectionHelper::closeConnection();
}

void DBModule::reconnect()
{
	disconnect();
	MSSQLConnectionHelper::initConnection(databaseInfo);
}
