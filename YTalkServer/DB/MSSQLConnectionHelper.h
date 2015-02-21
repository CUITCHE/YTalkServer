#ifndef MSSQLCONNECTIONHELPER_H
#define MSSQLCONNECTIONHELPER_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   12:21
	file base:	MSSQLConnectionHelper
	author:		CHE
	
	purpose:	采用odbc连接到MSSQL
				不采用prepare模式，此类不包含数据成员，采用prepare模式
				反而累赘
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
	//连接到数据库
	static QSqlError::ErrorType initConnection(const SettingInfo &info);

	//断开数据库连接
	static void closeConnection();

	//执行sql语句并返回行的结果集
	static const QSqlQuery  execQuery(const QString &execSql);

	//执行sql语句并返回行的数量，即受影响的行数，如：select,update,delete,insert等
	static int execDML(const QString &execSql);

	//执行sql语句并返回结果集的数量
	static int execScalar(const QString &execSql);
private:
	//检测数据是否处于open状态，open返回true
	static bool checkDB();
};

#endif // MSSQLCONNECTIONHELPER_H
