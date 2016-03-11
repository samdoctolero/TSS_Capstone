#include "Solar.h"
#include <wiringSerial.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>

//Command constants
#define READ_FUNC		"03"
#define AMPH_ADD_HI		"0013"
#define AMPH_ADD_LO		"0014"
#define BATT_ADD		"0009"
#define AH_RESET_ADD	"0010"
#define START_CHAR		":"
#define END_CHAR		"0DA0"
#define SLAVE_ADD		"0000"			//default address
#define SERIAL_NAME		"/dev/ttyUSB1"
#define P_LOG_FILE		"/powerLog"
#define NO_DATA			0x

using namespace std;

Solar::Solar(int baud)
:baudRate(baud), ampHour(0), accumAmpHour(0)
{
	serialObj = serialOpen(SERIAL_NAME, baudRate);
	if (serialObj = -1)
	{
		printf("Not initialized");
	}

	char currentPath[FILENAME_MAX];
	getcwd(currentPath, FILENAME_MAX];
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
	battPercent = 
}

void Solar::logData()
{
	//currPath->append(P_LOG_FILE);
	//ofstream configFile

}

void Solar::resetAmpHour()
{

}

static unsigned char Solar::LRC(auchMsg,usDataLen)
unsigned char *auchMsg;								/* message to calculate LRC upon */
unsigned short usDataLen;							/* quantity of bytes in message */
{
	unsigned char uchLRC = 0;						/* LRC char initialized */
	while (usDataLen––)								/* pass through message buffer */
		uchLRC += *auchMsg++;						/* add buffer byte without carry */
	return ((unsigned char)(–((char)uchLRC)));		/* return twos complement */
}

double Solar::readAmpHour()
{
	//string highResponse, lowResponse;
	//string msg = string(START_CHAR) + string(READ_FUNC) + string()
}

double Solar::readBattPercent()
{
	string msg = string(START_CHAR) + string(BATT_ADD) + string(READ_FUNC) + string("0003");
	string check = string(LRC(msg[0], string.size()));
	msg = msg + check + string(END_CHAR);
	serialPrintf(serialObj,msg);
	while (serialDataAvail(serialObj) <= 0){}; //Pretty much pause until the data is available
	serial response = "";
	while (serialDataAvail(serialObj) > 0)
	{
		response = string(serialGetChar(serialObj));
	}

	//First 7 characters are not needed
	string sVolt = 


}
