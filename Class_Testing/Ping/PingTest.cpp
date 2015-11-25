#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Ping.h" 

using namespace std;

int main()
{
	Ping proxSensor(0, 1, 2, 55.5);
	int gnd, pwr, cntl;
	double tol;
	proxSensor.getPins(gnd,pwr,cntl);
	tol = proxSensor.getTolerance();

	cout << "Ground: " << gnd << endl;
	cout << "Power: " << pwr << endl;
	cout << "Control: " << cntl << endl;
	cout << "Tolerance: " << tol << endl;


	return 0;
}