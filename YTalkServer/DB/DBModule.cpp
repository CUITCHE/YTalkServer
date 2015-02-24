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
	//�������ļ��ж�ȡ���ݿ�������Ϣ
	GET_INSTANCE(SettingHelper);
	databaseInfo = const_cast<SettingInfo*>(ins->getSettingInfo());
	QSqlError::ErrorType errorType;
	qDebug() << "****************���ݿ����ģ���ʼ��****************";
	qDebug() << "Ĭ������:";
	qDebug() << "���ݿ��������ַ:" << databaseInfo->getDBServerName();
	qDebug() << "���ݿ�������˿�:" << databaseInfo->getDBServerPort();
	qDebug() << "���ݿ�����:" << databaseInfo->getDBDatabaseName();
	qDebug() << "���ݿ��û���:" << databaseInfo->getDBUserName();
	qDebug() << "���ݿ�����:" << databaseInfo->getDBPassword();
	int trycount = -1;
	do 
	{
		++trycount;
		errorType = MSSQLConnectionHelper::initConnection(*databaseInfo);
		if (trycount > 0){
			qDebug() << "�������ݿ�ʧ��" << trycount << "�Σ�5�������������......";
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

bool DBModule::accountValidate(const QString &email, const QString &validateCode) const
{
	//֮����ܻ���������md5ֵ���ж�
	QDateTime curTime = QDateTime::currentDateTime();
	QString sql = QString("select identifydate from ytalk_user where mailAddress = '%1' AND identifycode='%2'")
		.arg(email)
		.arg(validateCode);
	auto ret = MSSQLConnectionHelper::execQuery(sql);
	if (!ret.next()){
		return false;
	}
	auto date = ret.value("identifydate").toDateTime();
	if (curTime < date){
		return true;
	}
	return false;
}
