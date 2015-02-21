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
	//��QObjectת����QVariant��
	static void qobject2qvariant(const QObject *object, QVariantMap &variant);

	//��QVariant�洢��QObject���е����ݳ�Ա��ȥ��
	static void qvariant2qobject(const QVariantMap &variant, QObject *object);
private:
	
};

#endif // ABSTRACTPASERJSON_H
