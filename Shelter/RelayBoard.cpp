#include "RelayBoard.h"
#include <wiringPi.h>


RelayBoard::RelayBoard(int control, double idleT, double minT)
:controlPin(control), bulbState(0), idleTemp(idleT), minEnvTemp(minT)
{
	pinMode(controlPin, OUTPUT);
}


RelayBoard::~RelayBoard()
{
}

void RelayBoard::setControlPin(int control)
{
	this->controlPin = control;;
}

unsigned int RelayBoard::getControlPin()
{
	return this->controlPin;
}

void RelayBoard::getTempSettings(double &idleT, double &minT)
{
	idleT = this->idleTemp;
	minT = this->minEnvTemp;
}

void RelayBoard::heatControl(double bulbTemp, double envTemp, bool objectPresent)
{
	//control the board and set the board's state
	int signal = 0;
	if (envTemp < this->minEnvTemp) //If the read enviro. temp. is lower than the min Temp of the bulb
	{
		if (objectPresent)//If someone is present in the shelter then turn on the bulb to the max
		{
			signal = 1;
			this->bulbState = MAX;
		}
		else // If no one is present then set the bulb to an idle state
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
	else // If the env. temp is greater than or equal to the min temp then keep it off
	{
		signal = 0;
		this->bulbState = OFF;
	}
	this->sendToRelay(signal); // send the signal to the relay
}

void RelayBoard::sendToRelay(int state)
{
	digitalWrite(this->controlPin, state);
}

