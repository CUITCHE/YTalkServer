#ifndef INSTANTIATIONPACKETHELPER_H
#define INSTANTIATIONPACKETHELPER_H
/********************************************************************
	created:	2015/02/22
	created:	22:2:2015   14:45
	file base:	InstantiationPacketHelper
	author:		CHE
	
	purpose:	���ݿͻ�����������ݰ���������Ӧ��Pakcet��
*********************************************************************/
class Pakcet;
class InstantiationPacketHelper
{
public:
	InstantiationPacketHelper();
	~InstantiationPacketHelper();
	//ͨ��Э��ţ�������Ӧ��Packet���ָ�����
	static Pakcet* getPacketByProtocol(const int protocol);
private:
	
};

#endif // INSTANTIATIONPACKETHELPER_H
