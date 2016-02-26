#include <iostream>
#include <wiringPi.h>
#include "Shelter.h"
#include <stdint.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <stdio.h>
#include <time.h>
//Devices
#include "IR.h"
#include "Ping.h"
#include "RelayBoard.h"
#include "TempHumid.h"
#include "ConfigManager.h"
#include "widget.h"

using namespace std;

Shelter::Shelter()
{
	run = true;
	//screenOn();
}

Shelter::~Shelter()
{
	
	delete bulbTemp; 
	delete proxSensor;
	delete bulbControl;
	delete tempHumid;
	delete gui;
	
}

void Shelter::mainLoop()
{
	time_t rawtime;
	struct * tm timeinfo;
	while (run)
	{
		//Grab all the data:
		double bulbT = bulbTemp->readObjTemp();						//Read temperature on heat bulbs
		double envTemp, humidity;
		tempHumid->PassTempAndHumid(envTemp, humidity);				//Read environment temperature and humidity(not used)
		bool objDetected = proxSensor->ObjectDetected();			//Read if an object is detected
		time(&rawtime);												//Read localtime
		timeinfo = localtime(&rawtime);

		//Output necessary info and control bulb or screen
		screenControl(objDetected);									//Turn on screen if object is present else turn it off
		bulbControl->heatControl(bulbT,envTemp,objDetected);		//Turn bulb ON/OFF depending on the environment temperature, bulb temperature, and if object is present
		
		//GUI Output
		gui.setTime("12:00A");
		string T = itoa(envTemp);
		T.append("C");
		gui.setTemperature(T);
		gui.setPower("100W");
		gui.setBusRouteInfo("1","2","3");
		gui.setBusRouteInfo("4", "5", "6");
		gui.setBusRouteInfo("7", "8", "9");
		gui.setBusRouteInfo("10", "11", "12");
		sleep(1);													//Delay
	}
	

	//screenOff();
	//screenOn();

}

void Shelter::initialize()
{
	ConfigManager config;
	config.ReadConfigFile();
	
	//allocate memory and create new instances
	//of each classes
	bulbTemp = new IR();
	proxSensor =  new Ping(config.ping_control, config.ping_tolerance, config.ping_run_time);
	bulbControl = new RelayBoard(config.relay_control, config.relay_idle_temperature, config.relay_minimum_temperature);
	tempHumid = new TempHumid(config.temp_humid_pin);
	//Set up gui
	gui = new widget();
	gui.setCursor(Qt::BlankCursor);
	gui.displayBusRouteInfor();
	gui.setTemperature("100C");
	gui.setTime("12:00A");
	gui.setPower("100W");
	gui.setBusRouteInfo("1", "2", "3");
	gui.setBusRouteInfo("4", "5", "6");
	gui.setBusRouteInfo("7", "8", "9");
	gui.setBusRouteInfo("10", "11", "12");
	gui.showFullScreen();

	stopPin = config.stop_pin;
	//wiringPi creates the connections in the backend
	wiringPiSetup();

	//inialize all the classes
	pinMode(stopPin, OUTPUT);
	digitalWrite(stopPin, HIGH);
	pinMode(stopPin, INPUT);

}

void Shelter::screenOff()
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

void Shelter::screenOn()
{
	if ((system("sudo tvservice -p") != 0) || system("sudo chvt 9 && sudo chvt 7") != 0 )
	{
		std::cout << "Cannot turn ON HDMI" << std::endl;
	}
	else
	{
		hdmiOn = true;
	}
}

void Shelter::screenControl(bool obj)
{
	//If an object exists turn on the screen, if it is off
	// otherwise turn if off, if it is on
	//hdmiOn is to avoid flickering screen due to constant turning on of the screen
	if (obj == true)
	{
		if (hdmiOn == false)
		{
			screenOn();
		}
	}
	else
	{
		if (hdmiOn == true)
		{
			screenOff();
		}
	}

}

void Shelter::stopButton(bool & check)
{
	int sig = digitalRead(stopPin);
	//std::cout << sig << std::endl;
	if (sig == 0)
	{
		//if the buttonn is pressed
		//return a false
		check = false;
	}
}