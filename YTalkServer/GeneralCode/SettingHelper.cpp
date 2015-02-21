#include "stdafx.h"
#include "SettingHelper.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QTextStream>
SettingHelper* SettingHelper::instance = nullptr;

SettingHelper::SettingHelper(QObject *parent)
	:AbstractParseJson(parent)
	, needFlush(false)
{
	fileCache = new QFile("db.setting.json");
	if (fileCache->open(QIODevice::ReadWrite) == false){
		QMessageBox::information(nullptr, "提示", "db.seeting.json配置文件不存在！", QMessageBox::Yes);
		exit(1);
	}
	auto data = fileCache->readAll();
	QJsonParseError error;
	QJsonDocument json = QJsonDocument::fromJson(data, &error);
	if (error.error != QJsonParseError::NoError){
		json = QJsonDocument::fromJson("{}");
	}
	auto info = json.toVariant().toMap();
	dbinfoCache = new DBInfo;
	qvariant2qobject(info, dbinfoCache);
}

SettingHelper::~SettingHelper()
{
	maybeNeedFlush();
	delete fileCache;
	delete dbinfoCache;
}

QVariant SettingHelper::getValue(const char *key)
{
	checkInstance();
	return instance->dbinfoCache->property(key);
}

void SettingHelper::setValue(const char *key, const QVariant &val)
{
	checkInstance();
	instance->dbinfoCache->setProperty(key, val);
	instance->needFlush = true;
}

void SettingHelper::checkInstance()
{
	if (instance == nullptr){
		instance = new SettingHelper;
	}
}

void SettingHelper::sync()
{
	instance->maybeNeedFlush();
}

void SettingHelper::maybeNeedFlush()
{
	if (needFlush == false){
		return;
	}
	
	QVariantMap variant;
	qobject2qvariant(dbinfoCache, variant);
	auto data = QJsonDocument::fromVariant(variant).toJson();
	QTextStream stream(fileCache);
	stream << data;
	fileCache->flush();
	needFlush = false;
}
