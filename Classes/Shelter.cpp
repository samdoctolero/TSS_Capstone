#include "Shelter.h"
#include "Ping.h""
#include <wiringPi.h>
#include "RelayBoard.h"
#include <string.h>
#include <fstream>
#include <array>
/*
	ADD THE LIBRARIES HERE
*/


/*
	ADD CONSTANTS HERE
*/

Shelter::Shelter()
:shelter_id(0x00), relayObj(RelayBoard(0, 0, -10, 100)), proximityObj(Ping(0,0,0,500))
{
	for (int i = 0; i < DEFAULT_NUM_BUS; i++)
	{
		bus[i].id = 0x00;
		bus[i].initial_time = 000000000;
		bus[i].number = 0;
		bus[i].num_stop_away = 0;
	}
}


Shelter::~Shelter()
{
}


void Shelter::Loop()
{
	bool running = true;
	while (running)
	{
		//Grab data from all sensors


		//Manipulate Data


		//Output to monitor


		//Output to heater


		//Check stopping condition
		//Make use of xBee to communicate stopping signal (i.e. setting running to FALSE)
		//This is useful when we want to shutdown the program
	}
}

void Shelter::readConfig()
{

}

void Shelter::processData()
{

}