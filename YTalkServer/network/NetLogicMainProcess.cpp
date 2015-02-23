#include "stdafx.h"
#include "NetLogicMainProcess.h"
#include "NetServerControl.h"
#include "InstantiationPacketHelper.h"
#include "Pakcet.h"
#ifdef __surrenderconsole__
#undef __surrenderconsole__
#endif
#define __surrenderconsole__ QThread::msleep(0);

NetLogicMainProcess::NetLogicMainProcess(QObject *parent)
	: QThread(parent)
	, m_socket(new NetServerControl(this))
	, active(false)
	, permit(false)
{
	connect(this, &QThread::finished, this, [&](){active = false; });
}

NetLogicMainProcess::~NetLogicMainProcess()
{
	if (isActive() == false){
		return;
	}
	stop();
	//等待2s
	bool ret = this->wait(2*1000);
	if (ret == false){
		//强制结束
		this->terminate();
	}
}

void NetLogicMainProcess::start()
{
	permit = true;
	QThread::start();
}

void NetLogicMainProcess::stop()
{
	permit = false;
}

bool NetLogicMainProcess::isActive() const
{
	return active == true;
}

void NetLogicMainProcess::run()
{
	active = true;
	NetCommunicationModule NCM;
	forever{
		if (permit == false){
			break;
		}
		if (m_socket->isPendingClientData() == false){
			__surrenderconsole__
			continue;
		}
		NCM = m_socket->getPendingData();
		this->task(NCM);
	}
}

void NetLogicMainProcess::task(const NetCommunicationModule &NCM)
{
	QTcpSocket *sock = NCM.sock;
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(NCM.data, &error);
	if (error.error != QJsonParseError::NoError){
		qDebug() << "json parse error! in" << __FUNCSIG__;
		qDebug() << "data of recieving is :\"" << NCM.data << "\"";
		return;
	}
	QVariantMap data = jsonDocument.toVariant().toMap();
	int protocol = Pakcet::Protocol(data);
	auto pck = InstantiationPacketHelper::getPacketByProtocol(protocol);
	pck->write(data);
	switch (protocol)
	{
	case Empty:
		//TODO:....
		break;
	default:
		break;
	}
}

