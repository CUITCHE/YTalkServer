#include "stdafx.h"
#include "DBModule.h"
#include "SettingHelper.h"
DBModule* DBModule::uniqueInstance = nullptr;

DBModule::DBModule(QObject *parent)
	:QThread(parent)
{
	uniqueInstance = this;
}

DBModule::~DBModule()
{

}

DBModule* DBModule::instance()
{
	if (uniqueInstance){
		return uniqueInstance;
	}
	return new DBModule;
}

void DBModule::deleteInstacen(DBModule *object)
{
	delete object;
}

void DBModule::initDBConnect()
{
	//�������ļ��ж�ȡ���ݿ�������Ϣ
	databaseInfo.serverName = SettingHelper::getValue("serverName").toString();
	databaseInfo.serverPort = SettingHelper::getValue("serverPort").toString();
	databaseInfo.databaseName = SettingHelper::getValue("databaseName").toString();
	databaseInfo.userName = SettingHelper::getValue("userName").toString();
	databaseInfo.password = SettingHelper::getValue("password").toString();
	QSqlError::ErrorType errorType;
	qDebug() << "****************���ݿ����ģ���ʼ��****************";
	qDebug() << "Ĭ������:";
	qDebug() << "���ݿ��������ַ:" << databaseInfo.serverName;
	qDebug() << "���ݿ�������˿�:" << databaseInfo.serverPort;
	qDebug() << "���ݿ�����:" << databaseInfo.databaseName;
	qDebug() << "���ݿ��û���:" << databaseInfo.userName;
	qDebug() << "���ݿ�����:" << databaseInfo.password;
	int trycount = -1;
	do 
	{
		++trycount;
		errorType = MSSQLConnectionHelper::initConnection(databaseInfo);
		if (trycount > 0){
			qDebug() << "�������ݿ�ʧ��" << trycount << "�Σ����ڳ�����������......";
			QThread::msleep(5 * 1000);
		}
	} while (errorType != QSqlError::NoError);
	qDebug() << "���ݿ����ӳɹ�!";
}
