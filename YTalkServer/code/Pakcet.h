#ifndef PAKCET_H
#define PAKCET_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   15:36
	file base:	Pakcet
	author:		CHE
	
	purpose:	包类的基础类，需要定义其它包类，需要继承此类
				通过wite() 把数据写入到数据成员
				通过read() 把数据序列化成json
*********************************************************************/
#include "AbstractParseJson.h"
#include "NetCommunicationProtocol.h"
using namespace net;
class QVariant;
class Pakcet : public AbstractParseJson
{
	Q_OBJECT

	QT_MOC_MINE_DEFINITION(int, protocol, Protocol);
public:
	Pakcet(NetCommunicationProtocol _protocol = Empty, QObject *parent = 0);
	virtual ~Pakcet();
};

#endif // PAKCET_H
