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
class QFile;
class SettingHelper
{
	PREPARE_INSTANCE_DECLARE(SettingHelper)
public:
	QVariant getValue(const char *key);
	void setValue(const char *key, const QVariant &val);

	//保存设置过的值到文件
	void sync();

	//获取配置对象
	const SettingInfo* getSettingInfo()const;
private:
	SettingHelper();
	~SettingHelper();

	//可能需要将数据保存到磁盘
	void maybeNeedFlush();
private:
	bool needFlush;
	QFile *fileCache;
	SettingInfo *dbinfoCache;		//服务配置缓存
};

#endif // SETTINGHELPER_H
