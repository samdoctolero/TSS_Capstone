#pragma once
#include <string>
#include <modbus.h>

using namespace std;

class Solar
{
public:
	Solar(int baud);
	~Solar();
	void updateData();
	void logData(); //call this function every hour to log the data for that day
	
	double getBattVoltage();
	double getChargeCurrent();
	double getLoadCurrent();
	double getPowerUsed();
	double getPowerCharged();
    int getBattPercent();
private:
	int baudRate;
	modbus_t * modBusObj; 
	double battVoltage;
	double chargeCurrent;
	double loadCurrent;
	double powerUsed;
	double powerCharged;
	string * currPath;
    int timeToday;
    double ampHourToday;
    double coeff[6];
};
