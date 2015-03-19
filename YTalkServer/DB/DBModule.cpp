#include "stdafx.h"
#include "DBModule.h"
#include "SettingHelper.h"
#include <QDateTime>
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
	auto ins = get<SettingHelper>();
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
		auto ins = get<SettingHelper>();
		databaseInfo = const_cast<SettingInfo*>(ins->getSettingInfo());
	}
	MSSQLConnectionHelper::initConnection(*databaseInfo);
}

void DBModule::testQuery() const
{
	QString sql = "insert into ytalk_user(mailAddress,password) values('dsfew',43231243)";
	MSSQLConnectionHelper::execDML(sql);
}

bool DBModule::accountValidate(const QString &email, const QString &validateCode) const
{
	//之后可能会加入密码的md5值的判断
	QDateTime curTime = QDateTime::currentDateTime();
	auto ret = MSSQLConnectionHelper::execQuery("select identifydate from ytalk_user where mailAddress = ? AND identifycode = ?",email, validateCode);
	if (!ret.next()){
		return false;
	}
	auto date = ret.value("identifydate").toDateTime();
	if (curTime < date){
		return true;
	}
	return false;
}

bool DBModule::userLogin(const QString &email, const QString &pwd, int &result) const
{
	auto ret = MSSQLConnectionHelper::execQuery("select active from ytalk_user where mailAddress = ? AND password = ?", email, pwd);
	result = 0;
	if (!ret.next()){
		result = 2;
		return false;
	}
	bool active = ret.value("active").toBool();
	if (active == false){
		result = 1;
		return false;
	}
	return true;
}

bool DBModule::userReg(const QString &email, const QString &pwd, const QDateTime &timeReg, const QString &whereReg) const
{
	if (userExist(email) == false){
		return false;
	}
	auto ret = MSSQLConnectionHelper::execDML("insert into ytalk_user(mailAddress,password,registerDate,registerWhere) values(?,?,?,?)",
		email, pwd, timeReg, whereReg);

	return ret == 1 ? true : false;
}

bool DBModule::userExist(const QString &email) const
{
	QString sql = QString().arg(email);
	auto ret = MSSQLConnectionHelper::execDML("select id from ytalk_user where mailAddress = ?", email);

	return ret == 1 ? true : false;
}
