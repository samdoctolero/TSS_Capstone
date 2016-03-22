#include <modbus.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <iostream>
#include "Solar.h"

//Command constants
#define SLAVE_ADD		0x0001			//default address
#define SERIAL_NAME		"/dev/ttyUSB1"
#define P_LOG_FILE		"/powerLog"


using namespace std;

Solar::Solar(int baud)
:baudRate(baud), battVoltage(0), chargeCurrent(0), loadCurrent(0), powerUsed(0), powerCharged(0)
{
	modBusObj = modbus_new_rtu(SERIAL_NAME,baud,'N',8,2);
	if (modBusObj == 0)
	{
		cout << "Not initialized" << endl;
	}
	else
	{
		int check = modbus_connect(modBusObj);
		if (check != 0)//0 means successful
		{
			cout << "Cannot connect: " <<check<< endl;
		}
		check = modbus_set_slave(modBusObj, 1);
		if (check != 0)
		{
			cout << "Cannot set slave ID number." << endl;
		}

		char currentPath[FILENAME_MAX];
		getcwd(currentPath, FILENAME_MAX);
		currPath = new string(currentPath);
	}
}

Solar::~Solar()
{
	delete currPath;
	modbus_close(modBusObj);
}

void Solar::updateData()
{
	uint16_t response[30];
	int check = modbus_read_registers(modBusObj, 1,29, response); //8 is arbitrary. It will give all the numbers
	if (check < 0)//means a zero
	{
		cout << "Unable to update data" << endl;
	}
	else
	{
		
		battVoltage = response[7] * 96.667 / 32768;
		chargeCurrent = response[10] * 66.667 / 32768;
		loadCurrent = response[11]*316.67 / 32768;
		powerUsed = battVoltage * loadCurrent;
		powerCharged = battVoltage * chargeCurrent;

		//cout << "Battery Voltage: " << battVoltage <<" Raw: "<<response[7]<< endl;
		//cout << "Charge Current: " << chargeCurrent <<"Raw: "<<response[11]<< endl;
		//cout << "Load Current: " << loadCurrent << "Raw: "<<response[12]<<endl;
		
		/*
		for (int i = 0; i < 30; i++)
		{
			cout << i + 1 << " : " << response[i] << endl;
		}
		*/
		
	}
	modbus_flush(modBusObj);
}

void Solar::logData()
{
	//currPath->append(P_LOG_FILE);
	//ofstream configFile

}
double Solar::getBattVoltage()
{
	return battVoltage;
}
double Solar::getChargeCurrent()
{
	return chargeCurrent;
}
double Solar::getLoadCurrent()
{
	return loadCurrent;
}
double Solar::getPowerUsed()
{
	return powerUsed;
}
double Solar::getPowerCharged()
{
	return powerCharged;
}