#include "stdafx.h"
#include "Transaction.h"
#include "DBModule.h"
#include "packets.h"
#include "NetLogicMainProcess.h"
#include <QMutex>
#include <QTcpSocket>
Transaction::Transaction(NetLogicMainProcess *parent)
	: QObject(parent->parent())
	, preparePacket(nullptr)
	, remoteSocket(nullptr)
	, prepareMutex(new QMutex)
	, netLogicMainProcess(parent)
{

}

Transaction::~Transaction()
{

}

void Transaction::lock(Packet *pct, QTcpSocket *sock)
{
	prepareMutex->lock();
	///从代码级别上保证preparePacket的唯一性【debug】
	Q_ASSERT(preparePacket == nullptr && remoteSocket == nullptr);
	remoteSocket = sock;
	preparePacket = pct;
}

void Transaction::unlock()
{
	preparePacket = nullptr;
	remoteSocket = nullptr;
	prepareMutex->unlock();
}

bool Transaction::userLogin()
{
	auto pck = dynamic_cast<UserLoginPacket *>(preparePacket);
	QString mail = pck->getMailAddress();
	QString pwd = pck->getPassword();
	auto d = get<DBModule>();
	int result = 0;
	bool ret = d->userLogin(mail, pwd, result);
	ServerBackPacket *pck2 = new ServerBackPacket;
	pck2->setOperator(pck->getProtocol());
	if (ret == false){
		pck2->setResult(result);
		switch (result)
		{
		case 1:
			pck2->setReason("您的帐号尚未激活");
			break;
		case 2:
			pck2->setReason("帐号或密码错误");
			break;
		}
	}
	else {
		pck2->setResult(0);
	}
	netLogicMainProcess->write(pck2, remoteSocket);
	return true;
}
