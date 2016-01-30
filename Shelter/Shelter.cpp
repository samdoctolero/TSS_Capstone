#include <iostream>
#include <wiringPi.h>
#include "Shelter.h"
#include <stdint.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <stdio.h>
//Devices
#include "IR.h"
#include "Ping.h"
#include "RelayBoard.h"
#include "TempHumid.h"
#include "ConfigManager.h"

using namespace std;

Shelter::Shelter()
{
	run = true;
	//screenOn();
}

Shelter::~Shelter()
{
	
	delete bulbTemp; 
	delete proxSensor;
	delete bulbControl;
	delete tempHumid;
	
}

void Shelter::mainLoop()
{
	
	while (run)
	{
		double envTemp, null;
		bool objDetected = proxSensor->ObjectDetected();
		cout << "Obj:" << objDetected << endl;
		tempHumid->PassTempAndHumid(envTemp, null);
		cout << envTemp << endl;
		bulbControl->heatControl(10, envTemp, objDetected);
		sleep(3);
	}
	

	//screenOff();
	//screenOn();

}

void Shelter::initialize()
{
	ConfigManager config;
	config.ReadConfigFile();
	
	//allocate memory and create new instances
	//of each classes
	bulbTemp = new IR();
	proxSensor =  new Ping(config.ping_control, config.ping_tolerance, config.ping_run_time);
	bulbControl = new RelayBoard(config.relay_control, config.relay_idle_temperature, config.relay_minimum_temperature);
	tempHumid = new TempHumid(config.temp_humid_pin);
	stopPin = config.stop_pin;

	//wiringPi creates the connections in the backend
	wiringPiSetup();

	//inialize all the classes
	pinMode(stopPin, OUTPUT);
	digitalWrite(stopPin, HIGH);
	pinMode(stopPin, INPUT);

}

void Shelter::screenOff()
{
	if (system("sudo tvservice -o") != 0)
	{
		std::cout << "Cannot turn OFF HDMI" << std::endl;
	}
	else
	{
		hdmiOn = false;
	}
}

void Shelter::screenOn()
{
	if ((system("sudo tvservice -p") != 0) || system("sudo chvt 9 && sudo chvt 7") != 0 )
	{
		std::cout << "Cannot turn ON HDMI" << std::endl;
	}
	else
	{
		hdmiOn = true;
	}
}

void Shelter::screenControl(bool obj)
{
	//If an object exists turn on the screen, if it is off
	// otherwise turn if off, if it is on
	//hdmiOn is to avoid flickering screen due to constant turning on of the screen
	if (obj == true)
	{
		if (hdmiOn == false)
		{
			screenOn();
		}
	}
	else
	{
		if (hdmiOn == true)
		{
			screenOff();
		}
	}

}

void Shelter::stopButton(bool & check)
{
	int sig = digitalRead(stopPin);
	//std::cout << sig << std::endl;
	if (sig == 0)
	{
		//if the buttonn is pressed
		//return a false
		check = false;
	}
}