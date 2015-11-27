#include <wiringPi.h> //Need to be installed on the Pi to be used
#include <ctime>
#include <cmath>
#include "Ping.h"

#define SOUND_SPEED 344 //speed of sound in meters per second

Ping::Ping(int gnd, int pwr, int control, double tol)
:GND_pin(gnd), PWR_pin(pwr), CONTROL_pin(control), dist_tolerance(tol), distance(0), accumTime(0);
{}

Ping::~Ping()
{
}

//Getters and Setters
void Ping::setPins(int gnd, int pwr, int control)
{
	this->GND_pin = gnd; this->PWR_pin = pwr; this->CONTROL_pin = control;
}

void Ping::setTolerance(double dist)
{
	this->dist_tolerance = dist;
}

void Ping::getPins(int &gnd, int &pwr, int &control)
{
	gnd = this->GND_pin; pwr = this->PWR_pin; control = this->CONTROL_pin;
}

double Ping::getTolerance()
{
	return this->dist_tolerance;
}

//Operation Functions
void Ping::updateDistance()
{
	int pin = this->CONTROL_pin;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, 0); //reset to zero
	delay(2);
	//start of transmission
	digitalWrite(pin, 1);
	delayMicroseconds(5);
	digitalWrite(pin, 0);
	//Activate PING to scan
	//Change pin mode to accept signals
	pinMode(pin, INPUT);
	delayMicroseconds(750);
	double utime = 0;
	while (digitalRead(pin) == 1)
	{
		delayMicroseconds(8);
		utime += 8;
	}
	//double dist = (utime / 2000) * SOUND_SPEED; // (t/2)*(344m/s)*(100cm/1m)*(1s/1000us)
	this->distance = utime*SOUND_SPEED / 2000; //cm
	this->accumTime = utime;
	delay(1000);
}

bool Ping::ObjectDetected()
{
	//IF distance > threshold return false else true
	return (this->distance > this->dist_tolerance) ? false : true;
}