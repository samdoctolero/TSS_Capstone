#pragma once

class ConfigManager
{
public:

	ConfigManager();
	~ConfigManager();

	int ping_control, relay_control, temp_humid_pin;
	double ping_tolerance, ping_run_time, relay_idle_temperature, relay_minimum_temperature;

	void ReadConfigFile();
};

