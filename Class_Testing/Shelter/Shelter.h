#pragma once
class Shelter
{
private:
	ConfigManager config;
	IR bulbTemp;
	Ping proxSensor;
	RelayBoard bulbControl;
	TempHumid tempHumid;

	bool run;
public:
	void mainLoop();
	void initialize();
};

