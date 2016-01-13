#pragma once
#include <string>
#include "serial.h"
class Communication
{
	struct Bus
	{
		int route;
		int numStopsAway;
		Bus * next;
	};
private:
	int busRoute, numStopsAway;
	t_serial * handle;
public:
	Communication();
	~Communication();
	bool init(std::string msg);
	void checkAndAcquireData(int &route, int &num);
	void sendMsg(std::string msg);
	std::string readMsg();
};

