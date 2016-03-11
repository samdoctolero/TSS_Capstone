#pragma once
#include <string>;

class Solar
{
public:
	Solar(int baud);
	~Solar();
	double getAccumAmpHour();
	double getBatteryPercent();
	double getDayAmpHour();
	double getAmpHour();
	void updateData();
	void logData(); //call this function every hour to log the data for that day

private:
	int baudRate;
	int serialObj; 
	double ampHour;
	double accumAmpHour;
	double dayAmpHour;
	double battPercent;
	string * currPath;

	void resetAmpHour();
	static unsigned char LRC(auchMsg, usDataLen);
	double readAmpHour();
	double readBattPercent();

};