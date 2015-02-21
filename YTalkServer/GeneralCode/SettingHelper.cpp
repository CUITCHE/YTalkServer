#include "stdafx.h"
#include "SettingHelper.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QTextStream>
PREPARE_INSTANCE_DEFINITION(SettingHelper);

SettingHelper::SettingHelper()
	: needFlush(false)
{
	fileCache = new QFile("db.setting.json");
	fileCache->open(QIODevice::ReadWrite);

	auto data = fileCache->readAll();
	QJsonParseError error;
	QJsonDocument json = QJsonDocument::fromJson(data, &error);
	if (error.error != QJsonParseError::NoError){
		json = QJsonDocument::fromJson("{}");
	}
	auto info = json.toVariant().toMap();
	dbinfoCache = new DBInfo;
	dbinfoCache->write(info);
}

SettingHelper::~SettingHelper()
{
	maybeNeedFlush();
	delete fileCache;
	delete dbinfoCache;
}

QVariant SettingHelper::getValue(const char *key)
{
	return dbinfoCache->getValue(key);
}

void SettingHelper::setValue(const char *key, const QVariant &val)
{
	dbinfoCache->setValue(key, val);
	needFlush = true;
}

void SettingHelper::sync()
{
	maybeNeedFlush();
}

void SettingHelper::maybeNeedFlush()
{
	if (needFlush == false){
		return;
	}
	
	QVariantMap variant = dbinfoCache->read();
	auto data = QJsonDocument::fromVariant(variant).toJson();
	QTextStream stream(fileCache);
	stream << data;
	fileCache->flush();
	needFlush = false;
}
