#include "Monitor.h"
#include <stdlib.h>

Monitor::Monitor(bool hdmi = true, bool en = true)
:hdmiOn(hdmi), controlEnabled(en)
{}

Monitor::~Monitor(){}

void Monitor::control(bool obj)
{
	if (controlEnabled)
	{
		if (obj == true)
		{
			if (hdmiOn == false)
			{
				turnOn();
			}
		}
		else
		{
			if (hdmiOn == true)
			{
				turnOff();
			}
		}
	}
}

void Monitor::turnOff()
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

void Monitor::turnOn()
{
	if ((system("sudo tvservice -p") != 0) || system("sudo chvt 9 && sudo chvt 7") != 0)
	{
		std::cout << "Cannot turn ON HDMI" << std::endl;
	}
	else
	{
		hdmiOn = true;
	}
}