#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "IR.h" 

using namespace std;

int main()
{
	IR bulbT; //Control pin = 15, and tolerance = 2 meters (since PING can only operate within 3m)
	while (true)
	{
		cout << "Object temperature is: " << bulbT.readObjTemp() <<" *C"<< endl;
		cout << "Die Temperature: " << bulbT.readDieTemp() << "*C" <<  endl;
		//cout << "Raw voltage: " << bulbT.readRawVoltage(bulbT.FD) << "V"<<endl;
		//printf("Raw Voltage: 0x%X\n", bulbT.readRawVoltage(bulbT.FD));
		sleep(4);
	}
	return 0;
}