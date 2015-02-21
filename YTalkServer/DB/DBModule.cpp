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
	//�������ļ��ж�ȡ���ݿ�������Ϣ
	GET_INSTANCE(SettingHelper);
	databaseInfo.serverName = ins->getValue("serverName").toString();
	databaseInfo.serverPort = ins->getValue("serverPort").toString();
	databaseInfo.databaseName = ins->getValue("databaseName").toString();
	databaseInfo.userName = ins->getValue("userName").toString();
	databaseInfo.password = ins->getValue("password").toString();
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
			qDebug() << "�������ݿ�ʧ��" << trycount << "�Σ�5�������������......";
			QThread::msleep(5 * 1000);
		}
	} while (errorType != QSqlError::NoError);
	qDebug() << "���ݿ����ӳɹ�!";
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
