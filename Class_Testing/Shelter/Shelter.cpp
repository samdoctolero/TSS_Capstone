#include <iostream>
#include <wiringPi.h>
#include "Shelter.h"
//Devices
#include "IR.h"
#include "Ping.h"
#include "RelayBoard.h"
#include "TempHumid.h"
#include "ConfigManager.h"

Shelter::Shelter()
{
	//Grab all the config files
	config = ConfigManager();
	config.ReadConfigFile();
	run = true;
}

Shelter::~Shelter()
{
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
	bulbTemp = IR();
	proxSensor = Ping(config.ping_control, config.ping_tolerance, config.ping_run_time);
	bulbControl = RelayBoard(config.relay_control, config.relay_idle_temperature, config.relay_minimum_temperature);
	tempHumid = TempHumid(config.temp_humid_pin)
	wiringPiSetup();
}