#ifndef SETTINGHELPER_H
#define SETTINGHELPER_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   13:38
	file base:	SettingHelper
	author:		CHE
	
	purpose:	配置文件读取和配置
*********************************************************************/
#include "MSSQLConnectionHelper.h"
#include "AbstractParseJson.h"
#include <QObject>
class QFile;
class SettingHelper: public AbstractParseJson
{
public:
	~SettingHelper();
	static QVariant getValue(const char *key);
	static void setValue(const char *key, const QVariant &val);
	//保存设置过的值到文件
	static void sync();
private:
	static void checkInstance();
	SettingHelper(QObject *parent = 0);

	//可能需要将数据保存到磁盘
	void maybeNeedFlush();
private:
	bool needFlush;
	QFile *fileCache;
	DBInfo *dbinfoCache;		//服务配置缓存
	static SettingHelper *instance;	//全局唯一的SettingHelper对象
};

#endif // SETTINGHELPER_H
