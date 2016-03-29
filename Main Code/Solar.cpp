#include <modbus.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cmath>
#include <errno.h>
#include "Solar.h"

//Command constants
#define SLAVE_ADD		0x0001			//default address
#define SERIAL_NAME		"/dev/ttyUSB1"
#define P_LOG_FILE		"/powerLog"


using namespace std;

Solar::Solar(int baud)
    :baudRate(baud), battVoltage(0), chargeCurrent(0), loadCurrent(0), powerUsed(0), powerCharged(0),ampHourToday(0)
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
        check = modbus_set_slave(modBusObj, SLAVE_ADD);
		if (check != 0)
		{
			cout << "Cannot set slave ID number." << endl;
		}
        check = modbus_rtu_set_serial_mode(modBusObj,MODBUS_RTU_RS232);
        if(check != 0)
        {
            cout<<"Unable to set serial mode for RS232"<<endl;
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
    int check = modbus_read_registers(modBusObj, SLAVE_ADD,30, response);
	if (check < 0)//means a zero
	{
		cout << "Unable to update data" << endl;
        fprintf(stderr,"%s\n",modbus_strerror(errno));
	}
	else
	{
		
        battVoltage = response[0] * 96.667 / 32768;
        chargeCurrent = response[3] * 66.667 / 32768;
        loadCurrent = response[4]*316.67 / 32768;
		powerUsed = battVoltage * loadCurrent;
		powerCharged = battVoltage * chargeCurrent;

        //cout << "Battery Voltage: " << battVoltage<<endl;
        //cout << "Charge Current: " << chargeCurrent <<" Raw: "<<response[11] <<endl;
        //cout << "Load Current: " << loadCurrent <<" Raw: "<<response[10] <<endl;
		
	}
	modbus_flush(modBusObj);
}

void Solar::logData()
{

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

int Solar::getBattPercent()
{
    if(battVoltage < 10.5){return 0;}
    double percent = 0;
    if(battVoltage >= 11.31)
    {
        percent = pow(10,3)*(0.0278*battVoltage*battVoltage - 0.5945*battVoltage + 3.1809);
    }
    else
    {
        percent = (10/(11.31-10.5))*battVoltage-129.629629;
    }

    cout<<"Percent: "<<percent<<endl;
    if(percent < 0){percent =  0;}
    if(percent > 100){percent = 100;}
    return (int)percent;
}
