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
:baudRate(baud), ampHour(0), accumAmpHour(0)
{
	modBusObj = modbus_new_rtu(SERIAL_NAME,baud,'N',8,2);
	if (modBusObj == 0)
	{
		cout << "Not initialized" << endl;
	}
	

	char currentPath[FILENAME_MAX];
	getcwd(currentPath, FILENAME_MAX);
	currPath = new string(currentPath);
}

Solar::~Solar()
{
	delete currPath;
}

double Solar::getAccumAmpHour()
{
	return accumAmpHour;
}

double Solar::getBatteryPercent()
{
	return battPercent;
}

double Solar::getAmpHour()
{
	return ampHour;
}

double Solar::getDayAmpHour()
{
	return dayAmpHour;
}

void Solar::updateData()
{
	battPercent = readBattPercent();
}

void Solar::logData()
{
	//currPath->append(P_LOG_FILE);
	//ofstream configFile

}

void Solar::resetAmpHour()
{

}

unsigned char Solar::LRC(unsigned char* auchMsg,int usDataLen)
//unsigned char *auchMsg;								/* message to calculate LRC upon */
//unsigned short usDataLen;							/* quantity of bytes in message */
{
						/* LRC char initialized */
	unsigned char uchLRC = 0;
	while (usDataLen--)								/* pass through message buffer */
		uchLRC += *auchMsg++;						/* add buffer byte without carry */
	return ((unsigned char)(-((char)uchLRC)));		/* return twos complement */
}

double Solar::readAmpHour()
{
	//string highResponse, lowResponse;
	//string msg = string(START_CHAR) + string(READ_FUNC) + string()
}

double Solar::readBattPercent()
{

}
