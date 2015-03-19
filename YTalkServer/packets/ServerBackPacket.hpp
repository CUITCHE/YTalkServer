#ifndef ServerBackPacket_H__
#define ServerBackPacket_H__

/********************************************************************
	created:	2015/03/19
	created:	19:3:2015   17:25
	file base:	ServerBackPacket
	author:		CHE
	
	purpose:	服务器“操作提示”返回类包
				约定：result=0->成功，其他值自行定义
*********************************************************************/
#include "Packet.h"

PACKET_DEFINITION_BEGIN(ServerBack)
Q_OBJECT
PACKET_STRUCTION(ServerBack)

QT_MOC_MINE_DEFINITION(int, Operator, Operator);
QT_MOC_MINE_DEFINITION(int, result, Result);
QT_MOC_MINE_DEFINITION(QString, reason, Reason);

PACKET_DEFINITION_END

#endif // ServerBackPacket_H__