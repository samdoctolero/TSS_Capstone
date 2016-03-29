#include <wiringPi.h> //Need to be installed on the Pi to be used
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Ping.h"

using namespace std;

Ping::Ping(int control, double tol, double runT)
:controlPin(control), dist_tolerance(tol), distance(0), runTime(runT), startTime(0), pausedState(false)
{
}

Ping::~Ping()
{
}

//Getters and Setters
void Ping::setControlPin(int control)
{
	controlPin = control;
}

void Ping::setTolerance(double dist)
{
	dist_tolerance = dist;
}

unsigned int Ping::getControlPin()
{
	return controlPin;
}

double Ping::getTolerance()
{
	return dist_tolerance;
}

double Ping::getDistance()
{
	return distance;
}
//Operation Functions

void Ping::initStartTime()
{
	startTime = micros();
	pausedState = true;
}

void Ping::updateDistance()
{
	int pin = controlPin;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, 0); //reset to zero
	delay(2);
	//start of transmission
	digitalWrite(pin, 1);
	delayMicroseconds(10);
	digitalWrite(pin, 0);
	//Activate PING to scan
	//Change pin mode to accept signals
	pinMode(pin, INPUT);
    //printf("Before while 1\n");
	while (digitalRead(pin) == 0){}
   // printf("While 1\n");
	long startTime = micros();
	while (digitalRead(pin) == 1){}
    //printf("While 2\n");
	//double dist = (utime / 2000) * SOUND_SPEED; // (t/2)*(344m/s)*(100cm/1m)*(1s/1000us)
	this->distance = (micros() - startTime) / 58; //cm
}

bool Ping::ObjectDetected()
{
    cout<<"Distance: "<<distance<<endl;
	if (((micros() - startTime) / 1000000 <= (runTime) * 60) && (pausedState == true))// Converted to seconds
	{
        //printf("If statement\n");
		return true;
	}
	else
	{
		updateDistance();
        //printf("Done update distance\n");
		pausedState = ((distance) / 100 > dist_tolerance) ? false : true;
		if (pausedState == true)
		{
			this->initStartTime();
		}
		return this->pausedState;
	}
	
}
