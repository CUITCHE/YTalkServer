#include "stdafx.h"
#include "Pakcet.h"

Pakcet::Pakcet(NetCommunicationProtocol _protocol, QObject *parent)
	: AbstractParseJson(parent)
	, protocol(_protocol)
{

}

Pakcet::~Pakcet()
{

}

int Pakcet::Protocol(const QVariantMap &json)
{
	return json.value("protocol").toInt();
}
