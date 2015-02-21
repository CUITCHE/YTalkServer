#ifndef TestPacket_H__
#define TestPacket_H__
#include "Pakcet.h"

class TestPacket :public Pakcet
{
	Q_OBJECT

	QT_MOC_MINE_DEFINITION(QString, name, Name);
	QT_MOC_MINE_DEFINITION(int, count, Count);
	QT_MOC_MINE_DEFINITION(QString, password, Password);
};

#endif // TestPacket_H__