#ifndef DBMODULE_H
#define DBMODULE_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   13:01
	file base:	DBModule
	author:		CHE
	
	purpose:	对数据库操作控制，利用prepare模式。把DBModule类
				改写为面向对象的类模式，而取消了静态调用操作
*********************************************************************/
#include "MSSQLConnectionHelper.h"
#include <QThread>
class QDateTime;
class DBModule: QThread
{
	PREPARE_INSTANCE_DECLARE(DBModule)
public:
	//初始化数据库连接
	void initConnect();

	//关闭数据库连接
	void disconnect();

	//重新连接数据库
	void reconnect();

	//test function
	void testQuery()const;

	//帐号验证服务
	bool accountValidate(const QString &email, const QString &validateCode) const;

	//用户登陆
	//result: 0无错误，1帐号未激活，2帐号或密码不存
	//只有返回值为false，result值才有意义
	bool userLogin(const QString &email, const QString &pwd, int &result)const;

	//用户注册
	bool userReg(const QString &email, const QString &pwd, const QDateTime &timeReg, const QString &whereReg)const;

	//用户是否存在
	bool userExist(const QString &email)const;
private:
	DBModule(QObject *parent = 0);
	~DBModule();
private:
	SettingInfo *databaseInfo;		//指针指向SettingHelper的数据成员，这里不做内存管理
};

#endif // DBMODULE_H
