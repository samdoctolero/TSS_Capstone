#include <wiringSerial.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <iostream>
#include <termios.h>
#include "Solar.h"

//Command constants
#define READ_FUNC		0x03
#define AMPH_ADD_HI		0x0013
#define AMPH_ADD_LO		0x0014
#define BATT_ADD		0x0009
#define AH_RESET_ADD	0x0010
#define START_CHAR		0x3A
#define END_CHAR		0x0DA0
#define SLAVE_ADD		0x0000			//default address
#define SERIAL_NAME		"/dev/ttyUSB0"
#define P_LOG_FILE		"/powerLog"
#define NO_DATA			0x

using namespace std;

Solar::Solar(int baud)
:baudRate(baud), ampHour(0), accumAmpHour(0)
{
	serialObj = serialOpen(SERIAL_NAME, baudRate);
	if (serialObj == -1)
	{
		cout << "Not initialized" << endl;
	}

	struct termios options;
	tcgetattr(serialObj, &options);
	options.c_cflag |= CSTOPB;
	tcsetattr(serialObj,0, &options);


	char currentPath[FILENAME_MAX];
	getcwd(currentPath, FILENAME_MAX);
	currPath = new string(currentPath);
}

Solar::~Solar()
{
	serialClose(serialObj);
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
	//Format:
	//|Start 1xchar|Address 2xchar|Function 2xchar|Data Nxchar|LRC 2xchar|End 2xchar|
	//Update ampHour

	//Update accumAmpHour

	//Update dayAmpHour

	//Update battPercent
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
	
	unsigned char msg[10] = { START_CHAR, 0x01, 0x03, 0x00, 0x6B, 0x00,0x03, 0x00, 0x0D, 0x0A };
	//string(START_CHAR) + string(BATT_ADD) + string(READ_FUNC) + string("0003");
	//unsigned char msg[18] = { '3', 'A', '0', '0', '0', '9', '0', '3', '0', '0', '0', '3', '5', '8', '0', 'D', '0', 'A' };
	unsigned char check = LRC(msg,10);
	cout << "Check int " << (int)check << endl;
	msg[7] = check;
	for (int i = 0; i < 10; i++)
	{
		serialPutchar(serialObj,msg[i]);
		cout <<i<<":" <<msg[i] << endl;
	}
	// cout << msg << endl;
	//serialPrintf(serialObj, msg);
	//cout << "Query sent..." <<msg<< endl;
	while (serialDataAvail(serialObj) <= 0)
	{
		cout << serialDataAvail(serialObj) << endl;
		sleep(1);
	} //Pretty much pause until the data is available
	int response = 0;
	while (serialDataAvail(serialObj) > 0)
	{
		response = serialGetchar(serialObj);
	}

	//First 7 characters are not needed
	cout << response << endl;
	
	return 1.0;
}
