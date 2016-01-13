#include "Communication.h"
//#include <wiringSerial.h>
#include "serial.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cctype>
#include <string.h>
//#include <termios.h>

//#define DATA_CMD	'A'
//#define PORT_NAME	"/dev/ttyACM0"
#define BAUD_RATE	115200
std::string port_name = "/dev/ttyACM0";

using namespace std;

Communication::Communication()
: busRoute(0), numStopsAway(0)
{
	handle = serial_new();
	serial_setBaud(handle, BAUD_RATE);
	if (serial_open(handle, &port_name[0]) < 0)
	{
		cout << "Error. Cannot open port: "<< port_name << endl;
		exit(0);
	}

	/*
	handle = serialOpen(PORT_NAME, BAUD_RATE);
	if (handle < 0)
	{
		std::cout << "Error. Cannot open port " << PORT_NAME << std::endl;
	}
	*/
	/*
	struct termios options;
	tcgetattr(handle, &options);
	options.c_cflag |= (CLOCAL | CREAD); //enable the receiver and set local mode
	options.c_cflag &= ~PARENB;			//No parity bit
	options.c_cflag &= ~CSTOPB;			// 1 stop bit
	options.c_cflag &= ~CSIZE;			//Mask Data size
	options.c_cflag |= CS8;				//Select 8 data bits
	options.c_cflag &= ~CRTSCTS;		// Disable hardware flow control
	//enable data to be processed as raw input
	options.c_lflag &= ~(ICANON | ECHO | ISIG);
	// set new attributes
	tcsetattr(handle, TCSANOW, &options);
	*/
}

Communication::~Communication()
{
	/*
	serialClose(handle);
	//Close all the Bus variables in memory
	*/
}

void Communication::sendMsg(string msg)
{
	//serialPrintf(handle, &msg[0]);
}

string Communication::readMsg()
{
	/*
	string data = "";
	while (serialDataAvail(handle) > 0)
	{
		cout << "Data available" << endl;
		char t = serialGetchar(handle);
		data.append(&t);
	}
	*/
}

bool Communication::init(string msg)
{
	/*
	serialPrintf(handle, &msg[0]);
	//sleep(5);
	cout << "Waiting for echo..." << endl;
	//cout << msg << endl;
	char echo = serialGetchar(handle);
	cout << echo << endl;
	if (echo != '+')
	{
		return false;
	}
	return true;
	*/
}
void Communication::checkAndAcquireData(int &route, int &num)
{
	/*
	route = busRoute;
	num = numStopsAway;
	if (serialDataAvail(handle)>0)
	{
		char first_byte; 
		first_byte = serialGetchar(handle);
		if (first_byte != DATA_CMD)
		{
			cout << "Not correct starting data line" << endl;
			return;
		}
		//Data format: AxxxBxxN
		string busNum = "";
		char t;
		do
		{
			t = serialGetchar(handle);
			busNum += t;
		} while (t != 'B');
		
		string stopAway = "";
		do
		{
			t = serialGetchar(handle);
			stopAway += t;
		} while (t != 'N');

		//flush the rest of the data
		serialFlush(handle);

		//if (isdigit(stopAway) && isdigit(busNum))
		//{
			busRoute = atoi(busNum.c_str());
			numStopsAway = atoi(stopAway.c_str());
			route = busRoute;
			num = numStopsAway;
		//}

	}
	return;
	*/
}
