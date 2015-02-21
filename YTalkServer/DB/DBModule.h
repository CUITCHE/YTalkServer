#ifndef DBMODULE_H
#define DBMODULE_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   13:01
	file base:	DBModule
	author:		CHE
	
	purpose:	�����ݿ��������
*********************************************************************/
#include "MSSQLConnectionHelper.h"
#include <QThread>
class DBModule: QThread
{
public:
	~DBModule();
	//��ȡȫ��Ψһ��DBModule
	static DBModule* instance();

	//ɾ��ָ����DBModule
	static void deleteInstacen(DBModule *object);

	void initDBConnect();
private:
	DBModule(QObject *parent = 0);
private:
	DBInfo databaseInfo;
	static DBModule *uniqueInstance;
};

#endif // DBMODULE_H
