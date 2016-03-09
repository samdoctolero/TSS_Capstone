#pragma once
#include <string>
class BusInfo
{
public:
	BusInfo(int num);
	~BusInfo();

	void updateData();
	int getNumStopAway();
	int getTimestamp();
	string getShelterID();
	
private:
	int busNum;
	string shelterId;
	int numStopAway;
	int timestamp; //epoch
	string currFolder;
};