#ifndef SETTINGHELPER_H
#define SETTINGHELPER_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   13:38
	file base:	SettingHelper
	author:		CHE
	
	purpose:	�����ļ���ȡ������
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
	//�������ù���ֵ���ļ�
	static void sync();
private:
	static void checkInstance();
	SettingHelper(QObject *parent = 0);

	//������Ҫ�����ݱ��浽����
	void maybeNeedFlush();
private:
	bool needFlush;
	QFile *fileCache;
	DBInfo *dbinfoCache;		//�������û���
	static SettingHelper *instance;	//ȫ��Ψһ��SettingHelper����
};

#endif // SETTINGHELPER_H
