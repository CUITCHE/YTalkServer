#ifndef PAKCET_H
#define PAKCET_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   15:36
	file base:	Packet
	author:		CHE
	
	purpose:	包类的基础类，需要定义其它包类，需要继承此类
				通过wite() 把数据写入到数据成员
				通过read() 把数据序列化成json
*********************************************************************/
#include "AbstractParseJson.h"
#include "NetCommunicationProtocol.h"
using namespace net;
class QVariant;
class Packet : public AbstractParseJson
{
	Q_OBJECT

	QT_MOC_MINE_DEFINITION(int, protocol, Protocol);
public:
	Packet(NetCommunicationProtocol _protocol = Empty, QObject *parent = 0);
	static int Protocol(const QVariantMap &json);
	virtual ~Packet();
};

#ifdef PACKET_STRUCTION
#undef PACKET_STRUCTION
#endif // PACKET_STRUCTION
#define PACKET_STRUCTION(PacketName) \
	public:\
	PacketName##Packet(NetCommunicationProtocol _protocol = net::PacketName):Packet(_protocol){}

#ifdef PACKET_DEFINITION_BEGIN
#undef PACKET_DEFINITION_BEGIN
#endif
#define PACKET_DEFINITION_BEGIN(PacketName)\
	class PacketName##Packet :public Packet {

#ifdef PACKET_DEFINITION_END
#undef PACKET_DEFINITION_END
#endif
#define PACKET_DEFINITION_END };

#endif // PAKCET_H
