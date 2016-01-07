#pragma once
#include <SerialStream.h>
#include <string>
class Communication
{
private:
	SerialStream * serial_port;
	int busRoute, numStopsAway;

public:

	Communication(int control, double idleT,double minT);
	~Communication();
	void checkAndAcquireData(int &route, int &num);

};

