#include "stdafx.h"
#include "MSSQLConnectionHelper.h"

QSqlError::ErrorType MSSQLConnectionHelper::initConnection(const DBInfo &info)
{
	QSqlDatabase mssqlDB = QSqlDatabase::addDatabase("QODBC");
	const QString dsn = QString("Driver={sql server};SERVER=%1;PORT=%2;DATABASE=%3;UID=%4;PWD=%5;")
		.arg(info.serverName)
		.arg(info.serverPort)
		.arg(info.databaseName)
		.arg(info.userName)
		.arg(info.password);
	//	QString dsn = "Driver={sql server};SERVER=222.18.159.25;PORT=1433;DATABASE=Queue_Share;UID=sa;PWD=Dbke6413;";
	mssqlDB.setDatabaseName(dsn);
	if (mssqlDB.open())
		qDebug() << "���ݿ����ӳɹ�!!!";
	else
		qDebug() << "���ݿ�����ʧ��!!!\n��ϸ������Ϣ:" << mssqlDB.lastError().databaseText();
	return mssqlDB.lastError().type();
}

void MSSQLConnectionHelper::closeConnection()
{
	QString connectionName;
	{
		QSqlDatabase mssqlDB = QSqlDatabase::database();
		if (mssqlDB.isOpen())
		{
			mssqlDB.close();
			connectionName = mssqlDB.connectionName();
		}
	}

	QSqlDatabase::removeDatabase(connectionName);
}

const QSqlQuery MSSQLConnectionHelper::execQuery(const QString &execSql)
{
	QSqlQuery query;
	checkDB();
	if (query.prepare(execSql))
	{
		if (query.exec())
			return query;
	}
	query.clear();
	return query;
}

int MSSQLConnectionHelper::execDML(const QString &execSql)
{
	QSqlQuery query;
	checkDB();
	if (query.prepare(execSql))
	{
		if (query.exec())
			return query.numRowsAffected();
	}
	return -1;
}

int MSSQLConnectionHelper::execScalar(const QString &execSql)
{
	QSqlQuery query;
	checkDB();
	if (query.prepare(execSql))
	{
		if (query.exec())
			return query.size();
	}
	return -1;
}

bool MSSQLConnectionHelper::checkDB()
{
	QSqlDatabase mssqlDB = QSqlDatabase::database();
	if (!mssqlDB.isOpen())
	{
		mssqlDB.open();
	}
	return mssqlDB.isOpen();
}