#include "RelayBoard.h"
#include <wiringPi.h>


RelayBoard::RelayBoard(int control, int ground, double idleT, double minT)
:controlPin(control), groundPin(ground), bulbState(0), idleTemp(idleT), minTemp(minT)
{
	pinMode(controlPin, OUTPUT);
}


RelayBoard::~RelayBoard()
{
}

void RelayBoard::setPins(int control, int ground)
{
	this->controlPin = control; this->groundPin = ground;
}

void RelayBoard::getPins(int &control, int &ground)
{
	control = this->controlPin; ground = this->groundPin;
}

void RelayBoard::getTemps(double &idleT, double &minT)
{
	idleT = this->idleTemp;
	minT = this->minTemp;
}

void RelayBoard::heatControl(double bulbTemp, double envTemp, bool objectPresent)
{
	//control the board and set the board's state
	int signal = 0;
	if (envTemp < this->minTemp)
	{
		if (objectPresent)
		{
			signal = 1;
			this->bulbState = MAX;
		}
		else
		{
			this->bulbState = IDLE;
			if (bulbTemp > this->idleTemp)
			{
				signal = 0;
			}
			else
			{
				signal = 1;
			}
		}
	}
	else
	{
		signal = 0;
		this->bulbState = OFF;
	}
	this->sendToRelay(signal);
}

void RelayBoard::sendToRelay(int state)
{
	digitalWrite(this->controlPin, state);
}

