#ifndef INSTANTIATIONPACKETHELPER_H
#define INSTANTIATIONPACKETHELPER_H
/********************************************************************
	created:	2015/02/22
	created:	22:2:2015   14:45
	file base:	InstantiationPacketHelper
	author:		CHE
	
	purpose:	根据客户端请求的数据包，生成相应的Pakcet类
*********************************************************************/
class Packet;
class InstantiationPacketHelper
{
public:
	InstantiationPacketHelper();
	~InstantiationPacketHelper();
	//通过协议号，返回相应的Packet类的指针对象
	static Packet* getPacketByProtocol(const int protocol);
private:
	
};
namespace net{
	Packet* get(const int protocol);
}

#endif // INSTANTIATIONPACKETHELPER_H
