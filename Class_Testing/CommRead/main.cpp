#include <iostream>
#include "BusInfo.h"

using namespace std;

int main()
{
	BusInfo busObj(10,"0x0001");
	busObj.updateData();
	cout << "Bus Number: " << busObj.getBusNum() << endl;
	cout << "Shelter ID: " << busObj.getShelterID() << endl;
	cout << "Bus is " << busObj.getNumStopAway() << " stops away" << endl;
	cout << "Timestamp: " << busObj.getTimestamp() << endl;
	return 0;
}