#ifndef TestPacket_H__
#define TestPacket_H__
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   22:25
	file base:	TestPacket
	author:		CHE
	
	purpose:	������
*********************************************************************/
#include "Pakcet.h"

class TestPacket :public Pakcet
{
	Q_OBJECT

	QT_MOC_MINE_DEFINITION(QString, name, Name);
	QT_MOC_MINE_DEFINITION(int, count, Count);
	QT_MOC_MINE_DEFINITION(QString, password, Password);
};

#endif // TestPacket_H__