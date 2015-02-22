#include "stdafx.h"
#include "NetCommunicationProtocol.h"
#include "InstantiationPacketHelper.h"
#include "test/TestPacket.hpp"

using namespace net;

InstantiationPacketHelper::InstantiationPacketHelper()
{

}

InstantiationPacketHelper::~InstantiationPacketHelper()
{

}

Pakcet* InstantiationPacketHelper::getPacketByProtocol(const int protocol)
{
	Pakcet *pck = nullptr;
	switch (protocol)
	{
	case Empty:
		pck = new Pakcet;
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
