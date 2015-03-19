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
	template<typename... Args>
	static const QSqlQuery execQuery(const QString &execSql, const Args&... args)
	{
		QSqlQuery query;
		query.prepare(execSql);
		execSql_impl(query, args...);
		execQuery(query);
		return query;
	}

	//执行sql语句并返回行的数量，即受影响的行数，如：select,update,delete,insert等
	template<typename... Args>
	static int execDML(const QString &execSql, const Args&... args)
	{
		QSqlQuery query;
		query.prepare(execSql);
		execSql_impl(query, args...);
		return execDML(query);
	}

	//执行sql语句并返回结果集的数量
	template<typename... Args>
	inline static int execScalar(const QString &execSql, const Args&... args)
	{
		QSqlQuery query;
		query.prepare(execSql);
		execSql_impl(query, args...);
		return execScalar(query);
	}
protected:
	//[模版] 给sql语句添加参数
	static void execSql_impl(QSqlQuery &query){}
	template<typename SqlType, typename... Args>
	static void execSql_impl(QSqlQuery &query, const SqlType &d, const Args& ...args){
		query.addBindValue(d);
		execSql_impl(query, args...);
	}

	//执行sql语句并返回行的结果集
	static void execQuery(QSqlQuery &query);

	//执行sql语句并返回行的数量，即受影响的行数，如：select,update,delete,insert等
	static int execDML(QSqlQuery &query);

	//执行sql语句并返回结果集的数量
	static int execScalar(QSqlQuery &query);

private:
	//检测数据是否处于open状态，open返回true
	static bool checkDB();
};

#endif // MSSQLCONNECTIONHELPER_H
