#include "stdafx.h"
#include "NetCommunicationProtocol.h"
#include "InstantiationPacketHelper.h"
#include "packets.h"

using namespace net;

InstantiationPacketHelper::InstantiationPacketHelper()
{

}

InstantiationPacketHelper::~InstantiationPacketHelper()
{

}

Packet* InstantiationPacketHelper::getPacketByProtocol(const int protocol)
{
	Packet *pck = nullptr;
	switch (protocol)
	{
	case Empty:
		pck = new Packet;
		break;
	case Test:
		pck = new TestPacket;
		break;
	default:
		__debugbreak();
		break;
	}
	return pck;
}
namespace net{
	Packet* get(const int protocol)
	{
		return InstantiationPacketHelper::getPacketByProtocol(protocol);
	}
}
