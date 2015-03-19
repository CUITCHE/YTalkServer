#ifndef NetCommunicationProtocol_H__
#define NetCommunicationProtocol_H__

/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   15:29
	file base:	NetCommunicationProtocol
	author:		CHE
	
	purpose:	网络通信协议
				主要是pakcet包协议的定义
*********************************************************************/
namespace net{
	enum NetCommunicationProtocol{
		Empty,
		Test,
		UserLogin,
		ServerBack,
	};
}
#endif // NetCommunicationProtocol_H__
