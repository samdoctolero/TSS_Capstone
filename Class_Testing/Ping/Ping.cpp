#include <wiringPi.h> //Need to be installed on the Pi to be used
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Ping.h"


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
	this->controlPin = control;
}

void Ping::setTolerance(double dist)
{
	this->dist_tolerance = dist;
}

unsigned int Ping::getControlPin()
{
	return controlPin;
}

double Ping::getTolerance()
{
	return this->dist_tolerance;
}

double Ping::getDistance()
{
	return this->distance;
}
//Operation Functions

void Ping::initStartTime()
{
	this->startTime = micros();
	this->pausedState = true;
}

void Ping::updateDistance()
{
	int pin = this->controlPin;
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
	while (digitalRead(pin) == 0){}
	long startTime = micros();
	while (digitalRead(pin) == 1){}
	//double dist = (utime / 2000) * SOUND_SPEED; // (t/2)*(344m/s)*(100cm/1m)*(1s/1000us)
	this->distance = (micros() - startTime) / 58; //cm
}

bool Ping::ObjectDetected()
{
	//IF distance > threshold return false else true
	//convert cm to meters
	if (((micros() - this->startTime) / 1000000 <= (this->runTime) * 60) && (this->pausedState == true))// Converted to seconds
	{
		return true;
	}
	else
	{
		this->updateDistance();
		this->pausedState = ((this->distance) / 100 > this->dist_tolerance) ? false : true;
		if (pausedState == true)
		{
			this->initStartTime();
		}
		return this->pausedState;
	}
	
}