#pragma once
#include <string>
class BusInfo
{
public:
	BusInfo(int num, string ID);
	~BusInfo();

	void updateData();
	int getNumStopAway();
	int getTimestamp();
	string getShelterID();
	int getBusNum();
	
private:
	int busNum;
	string shelterId;
	int numStopAway;
	int timestamp; //epoch
	string currFolder;
};