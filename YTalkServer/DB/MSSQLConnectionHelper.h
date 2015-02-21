#ifndef MSSQLCONNECTIONHELPER_H
#define MSSQLCONNECTIONHELPER_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   12:21
	file base:	MSSQLConnectionHelper
	author:		CHE
	
	purpose:	����odbc���ӵ�MSSQL
				������prepareģʽ�����಻�������ݳ�Ա������prepareģʽ
				������׸
*********************************************************************/
#include "SettingInfo.h"
#include <QtSql/QSql>
#include <QSqlQuery>
#include <QSqlError>

class MSSQLConnectionHelper
{
public:
	MSSQLConnectionHelper() = delete;
	~MSSQLConnectionHelper() = delete;
	//���ӵ����ݿ�
	static QSqlError::ErrorType initConnection(const SettingInfo &info);

	//�Ͽ����ݿ�����
	static void closeConnection();

	//ִ��sql��䲢�����еĽ����
	static const QSqlQuery  execQuery(const QString &execSql);

	//ִ��sql��䲢�����е�����������Ӱ����������磺select,update,delete,insert��
	static int execDML(const QString &execSql);

	//ִ��sql��䲢���ؽ����������
	static int execScalar(const QString &execSql);
private:
	//��������Ƿ���open״̬��open����true
	static bool checkDB();
};

#endif // MSSQLCONNECTIONHELPER_H
