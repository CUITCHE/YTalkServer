#ifndef UserLoginPacket_H__
#define UserLoginPacket_H__

/********************************************************************
	created:	2015/03/19
	created:	19:3:2015   12:22
	file base:	UserLoginPacket
	author:		CHE
	
	purpose:	用户登陆请求包
*********************************************************************/
#include "Packet.h"

PACKET_DEFINITION_BEGIN(UserLogin)
Q_OBJECT
PACKET_STRUCTION(UserLogin)
QT_MOC_MINE_DEFINITION(QString, mailAddress, MailAddress);
QT_MOC_MINE_DEFINITION(QString, password, Password);

PACKET_DEFINITION_END

#endif // UserLoginPacket_H__
