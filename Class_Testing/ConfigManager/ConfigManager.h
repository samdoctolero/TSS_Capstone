#pragma once

class ConfigManager
{
public:
	struct Bus
	{
		int number,			//bus number
		num_stop_away,		//number of stops away from this stop/shelter
		id;				//bus id
		double initial_time;//time since last update for a certain bus
	};

	ConfigManager();
	~ConfigManager();

	int ping_ground, ping_power, ping_control;
	double ping_distance_tolerance;
	int relay_ground, relay_control;
	double relay_idle_temperature, relay_env_min_temperature;

	Bus bus[10]; //borrowed a structure from Shelter class
	//More configuration files later
	void ReadConfigFile();
};

