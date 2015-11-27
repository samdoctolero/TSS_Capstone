#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Ping.h" 
#include <wiringPi.h>

using namespace std;

int main()
{
	wiringPiSetup();
	Ping proxSensor(0, 1, 2, 55.5);
	//int gnd, pwr, cntl;
	//double tol;
	//proxSensor.getPins(gnd,pwr,cntl);
	//tol = proxSensor.getTolerance();

	//cout << "Ground: " << gnd << endl;
	//cout << "Power: " << pwr << endl;
	//cout << "Control: " << cntl << endl;
	//cout << "Tolerance: " << tol << endl;
	int one;
	do {
		cin >> one;
		proxSensor.updateDistance();
		cout << "Time in microsecond that the pin was high: " << proxSensor.accumTime << endl;

	} while (one == 1)

	return 0;
}