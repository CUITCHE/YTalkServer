#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "SettingHelper.h"
#include "test/TestPacket.hpp"
#include "NetServerControl.h"
#include <algorithm>
using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QList<shared_ptr<int>> cont;
	cont.push_back(shared_ptr<int>(new int(2)));
	cont.push_back(shared_ptr<int>(new int(3)));
	int *abc = new int(4);
	cont.push_back(shared_ptr<int>(abc));
	cont.push_back(shared_ptr<int>(new int(5)));
	cont.push_back(shared_ptr<int>(new int(6)));
	auto ret = std::remove_if(cont.begin(), cont.end(), [=](const shared_ptr<int> &val){return val.get() == abc; });
	cont.push_back(shared_ptr<int>(new int(7)));;
	cont.erase(ret);
	return a.exec();
}
