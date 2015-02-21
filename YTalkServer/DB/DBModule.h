#ifndef DBMODULE_H
#define DBMODULE_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   13:01
	file base:	DBModule
	author:		CHE
	
	purpose:	对数据库操作控制
*********************************************************************/
#include "MSSQLConnectionHelper.h"
#include <QThread>
class DBModule: QThread
{
public:
	~DBModule();
	//获取全局唯一的DBModule
	static DBModule* instance();

	//删除指定的DBModule
	static void deleteInstacen(DBModule *object);

	void initDBConnect();
private:
	DBModule(QObject *parent = 0);
private:
	DBInfo databaseInfo;
	static DBModule *uniqueInstance;
};

#endif // DBMODULE_H
