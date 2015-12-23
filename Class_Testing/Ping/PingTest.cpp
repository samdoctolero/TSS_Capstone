#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Ping.h" 
#include <wiringPi.h>

using namespace std;

int main()
{
	wiringPiSetup();
	Ping proxSensor(1,2,0.5); //Control pin = 15, and tolerance = 2 meters (since PING can only operate within 3m)

	//Accumulate data on how the time and distance relate


		/*
		if (!proxSensor.Paused())
		{
			if (proxSensor.ObjectDetected())
			{
				proxSensor.initStartTime();
				cout << "Object DETECTED" << endl;
			}
			else
			{
				cout << "Object NOT DETECTED" << endl;
			}
			cout << "Distance recorded: " << proxSensor.getDistance() << endl;
		}
		else
		{
			cout << "Paused mode" << endl;
		}*/
	while (true)
	{
		if (proxSensor.Paused())
		{
			cout << "Object detected. Still within the paused state." << endl;
		}
		else
		{
			if (proxSensor.ObjectDetected())
			{
				proxSensor.initStartTime();
				cout << "Object detected. Initialized start time." << endl;
			}
			else
			{
				cout << "No Object within reach." << endl;
			}
		}

	}

	return 0;
}