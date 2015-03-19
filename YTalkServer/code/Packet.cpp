#include "stdafx.h"
#include "Packet.h"

Packet::Packet(NetCommunicationProtocol _protocol, QObject *parent)
	: AbstractParseJson(parent)
	, protocol(_protocol)
{

}

Packet::~Packet()
{

}

int Packet::Protocol(const QVariantMap &json)
{
	return json.value("protocol").toInt();
}
