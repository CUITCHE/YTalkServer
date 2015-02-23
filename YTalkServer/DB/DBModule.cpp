#include "stdafx.h"
#include "DBModule.h"
#include "SettingHelper.h"
PREPARE_INSTANCE_DEFINITION(DBModule);

DBModule::DBModule(QObject *parent)
	:QThread(parent)
	, databaseInfo(nullptr)
{
}

DBModule::~DBModule()
{

}

void DBModule::initConnect()
{
	//从配置文件中读取数据库的相关信息
	GET_INSTANCE(SettingHelper);
	databaseInfo = const_cast<SettingInfo*>(ins->getSettingInfo());
	QSqlError::ErrorType errorType;
	qDebug() << "****************数据库服务模块初始化****************";
	qDebug() << "默认配置:";
	qDebug() << "数据库服务器地址:" << databaseInfo->getDBServerName();
	qDebug() << "数据库服务器端口:" << databaseInfo->getDBServerPort();
	qDebug() << "数据库名称:" << databaseInfo->getDBDatabaseName();
	qDebug() << "数据库用户名:" << databaseInfo->getDBUserName();
	qDebug() << "数据库密码:" << databaseInfo->getDBPassword();
	int trycount = -1;
	do 
	{
		++trycount;
		errorType = MSSQLConnectionHelper::initConnection(*databaseInfo);
		if (trycount > 0){
			qDebug() << "连接数据库失败" << trycount << "次，5秒后尝试重新连接......";
			QThread::msleep(5 * 1000);
		}
	} while (errorType != QSqlError::NoError);
}

void DBModule::disconnect()
{
	MSSQLConnectionHelper::closeConnection();
}

void DBModule::reconnect()
{
	disconnect();
	if (databaseInfo == nullptr){
		GET_INSTANCE(SettingHelper);
		databaseInfo = const_cast<SettingInfo*>(ins->getSettingInfo());
	}
	MSSQLConnectionHelper::initConnection(*databaseInfo);
}

void DBModule::testQuery() const
{
	QString sql = "insert into ytalk_user(mailAddress,password) values('dsfew',43231243)";
	MSSQLConnectionHelper::execDML(sql);
}
