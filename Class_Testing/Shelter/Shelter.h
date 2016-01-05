#pragma once
#include <stdint.h>
#include "IR.h"
#include "Ping.h"
#include "RelayBoard.h"
#include "TempHumid.h"
#include "ConfigManager.h"


class Shelter
{
private:
	IR * bulbTemp;
	Ping  * proxSensor;
	RelayBoard * bulbControl;
	TempHumid  * tempHumid;

	bool run;

	void screenOn();
	void screenOff();
public:
	Shelter();
	~Shelter();
	void mainLoop();
	void initialize();
};

