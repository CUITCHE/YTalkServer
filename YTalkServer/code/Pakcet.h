#ifndef PAKCET_H
#define PAKCET_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   15:36
	file base:	Pakcet
	author:		CHE
	
	purpose:	����Ļ����࣬��Ҫ�����������࣬��Ҫ�̳д���
				ͨ��wite() ������д�뵽���ݳ�Ա
				ͨ��read() ���������л���json
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
