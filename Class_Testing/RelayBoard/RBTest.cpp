#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "RelayBoard.h" 
#include <wiringPi.h>
#include <unistd.h>

using namespace std;

int main()
{
	wiringPiSetup();
	RelayBoard RB(0, 100, -10); //Control pin at WiringPi pin 0, idle temp at 100*C and min environment temp at -10*C
	//Test Cases
	cout << "Case 1" << endl;
	RB.heatControl(90,-11,1);
	sleep(5);
	cout << "Case 2" << endl;
	RB.heatControl(90, -20, 0);
	sleep(5);
	cout << "Case 3" << endl;
	RB.heatControl(110, -25, 0);
	sleep(5);
	cout << "Case 4" << endl;
	RB.heatControl(100, 0, 1);
	sleep(5);
	cout << "Case 5" << endl;
	RB.heatControl(10,10,1);
	sleep(3);

	return 0;
}