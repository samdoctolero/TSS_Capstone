#pragma once
#include "Shelter.h"

class ConfigManager
{
public:
	ConfigManager();
	~ConfigManager();

	int ping_ground, ping_power, ping_control;
	double ping_distance_tolerance;
	int relay_ground, relay_control;
	double relay_idle_temperature, relay_env_min_temperature;

	Shelter::Bus bus[DEFAULT_NUM_BUS]; //borrowed a structure from Shelter class
	//More configuration files later
	void ReadConfigFile();
};

