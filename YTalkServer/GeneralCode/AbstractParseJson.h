#ifndef ABSTRACTPARSEJSON_H
#define ABSTRACTPARSEJSON_H

#include <QObject>
#include <QJsonDocument>
class AbstractParseJson : public QObject
{
	Q_OBJECT

public:
	AbstractParseJson(QObject *parent = 0);
	virtual ~AbstractParseJson();
	//将QObject转换成QVariant。
	static void qobject2qvariant(const QObject *object, QVariantMap &variant);

	//将QVariant存储到QObject类中的数据成员中去。
	static void qvariant2qobject(const QVariantMap &variant, QObject *object);
private:
	
};

#endif // ABSTRACTPASERJSON_H
