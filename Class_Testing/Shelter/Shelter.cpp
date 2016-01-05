#include <iostream>
#include <wiringPi.h>
#include "Shelter.h"
#include <stdint.h>
#include <cstdlib.h>
#include <unistd.h>
//Devices
#include "IR.h"
#include "Ping.h"
#include "RelayBoard.h"
#include "TempHumid.h"
#include "ConfigManager.h"

Shelter::Shelter()
{
	run = true;
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
	/*
	while (run)
	{
		std::cout << "Success!" << std::endl;
	}
	*/

	screenOff();
	sleep(5);
	screenOn();

}

void Shelter::initialize()
{
	ConfigManager config;
	config.ReadConfigFile();
	
	bulbTemp = new IR();
	proxSensor = new Ping(config.ping_control, config.ping_tolerance, config.ping_run_time);
	bulbControl = new RelayBoard(config.relay_control, config.relay_idle_temperature, config.relay_minimum_temperature);
	tempHumid = new TempHumid(config.temp_humid_pin);
	
	wiringPiSetup();
}

void Shelter::screenOn()
{
	if (system("sudo tvservice -o") != 0)
	{
		std::cout << "Cannot turn OFF HDMI" << std::endl;
	}
}

void Shelter::screenOff()
{
	if ((system("sudo tvservice -p") != 0) || system("sudo chvt 9 && sudo chvt 7") != 0 )
	{
		std::cout << "Cannot turn ON HDMI" << std::endl;
	}
}