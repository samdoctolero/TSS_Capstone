#include <iostream>
#include <wiringPi.h>
#include "Shelter.h"
#include <stdint.h>
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
	while (run)
	{
		std::cout << "Success!" << std::endl;
	}
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