#pragma once
#include <string>

using namespace std;

class ConfigManager
{
public:
    struct Bus
    {
        int num;
        string id;
    };
	ConfigManager();
	~ConfigManager();

	int ping_control, relay_control, temp_humid_pin,stop_pin,ir_address;
	double ping_tolerance, ping_run_time, relay_idle_temperature, relay_minimum_temperature;
    Bus busInfo[10];
	bool monitor_enabled;
	int control_timeout, solar_timeout, bus_timeout;

	void ReadConfigFile();
};

