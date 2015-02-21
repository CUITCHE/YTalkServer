#include "stdafx.h"
#include "AbstractParseJson.h"

AbstractParseJson::AbstractParseJson(QObject *parent)
	: QObject(parent)
{

}

AbstractParseJson::~AbstractParseJson()
{

}

void AbstractParseJson::qobject2qvariant(const QObject *object, QVariantMap &variant)
{
	const QMetaObject *metaobject = object->metaObject();
	int count = metaobject->propertyCount();
	for (int i = 1; i < count; ++i){
		QMetaProperty metaProperty = metaobject->property(i);
		const char *name = metaProperty.name();
		QVariant value = object->property(name);
		variant[QLatin1String(name)] = value;
	}
}

void AbstractParseJson::qvariant2qobject(const QVariantMap &variant, QObject *object)
{
	const QMetaObject *metaobject = object->metaObject();
	QVariantMap::const_iterator iter = variant.constBegin();
	int index = -1;
	while (iter != variant.end()){
		index = metaobject->indexOfProperty(iter.key().toLatin1());
		if (index < 0)continue;
		QMetaProperty metaProperty = metaobject->property(index);
		QVariant::Type type = metaProperty.type();
		QVariant v(iter.value());
		if (v.canConvert(type)){
			v.convert(type);
			metaProperty.write(object, v);
		}
		else if (QString(QLatin1String("QVariant")).compare(QLatin1String(metaProperty.typeName())) == 0){
			metaProperty.write(object, v);
		}
		++iter;
	}
}
