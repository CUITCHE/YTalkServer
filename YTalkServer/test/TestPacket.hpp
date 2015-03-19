#ifndef TestPacket_H__
#define TestPacket_H__
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   22:25
	file base:	TestPacket
	author:		CHE
	
	purpose:	≤‚ ‘¿‡
*********************************************************************/
#include "Packet.h"

class TestPacket :public Packet
{
	Q_OBJECT

	PACKET_STRUCTION(Test)
	QT_MOC_MINE_DEFINITION(QString, name, Name);
	QT_MOC_MINE_DEFINITION(int, count, Count);
	QT_MOC_MINE_DEFINITION(QString, password, Password);
};

#endif // TestPacket_H__