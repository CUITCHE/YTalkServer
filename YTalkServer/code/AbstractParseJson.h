#ifndef ABSTRACTPARSEJSON_H
#define ABSTRACTPARSEJSON_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   15:23
	file base:	AbstractParseJson
	author:		CHE
	
	purpose:	只要继承此类，则类可以把自己的数据成员序列化，
				形成json序列，key为数据成员名字
*********************************************************************/
#include "defs.h"
#include <QObject>
#include <QJsonDocument>
class AbstractParseJson : public QObject
{
	Q_OBJECT

public:
	AbstractParseJson(QObject *parent = 0);
	virtual ~AbstractParseJson();
	//将QObject转换成QVariant。
	void qobject2qvariant(QVariantMap &variant);

	//将QVariant存储到QObject类中的数据成员中去。
	void qvariant2qobject(const QVariantMap &variant);

	//获取指定数据成员的property
	QVariant getValue(const char *key) const;

	//设置指定数据成员的property
	void setValue(const char *key, const QVariant &val);

	//从序列化json数据中提取数据，实例化到类的成员
	void write(const QVariantMap &val);

	//读取数据成员，序列化为json数据
	QVariantMap read();
};

#endif // ABSTRACTPASERJSON_H
