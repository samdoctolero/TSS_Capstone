#include "Communication.h"
#include <SerialStream.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cctype>
#include <string>

#define DATA_CMD	'A'
#define PORT_NAME	"/dev/ttyUSB0"


Communication::Communication()
: busRoute(0), numStopsAway(0)
{
	serial_port = new SerialStream();
	serial_port->Open(PORT_NAME);
	if (!serial_port->good())
	{
		std::cout << "Cannot open port " << PORT_NAME << std::endl;
		exit(1);
	}
	serial_port->SetBaudRate(SerialStreamBuf::BAUD_9600);
	if (!serial_port->good())
	{
		std::cout << "Error cannot set Baud Rate"<< std::endl;
		exit(1);
	}
	serial_port->SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
	if (!serial_port->good())
	{
		std::cout << "Error: Could not set the character size." << std::endl;
		exit(1);
	}
	//
	// Disable parity.
	//
	serial_port->SetParity(SerialStreamBuf::PARITY_NONE);
	if (!serial_port->good())
	{
		std::cout << "Error: Could not disable the parity." << std::endl;
		exit(1);
	}
	//
	// Set the number of stop bits.
	//
	serial_port->SetNumOfStopBits(1);
	if (!serial_port->good())
	{
		std::cout << "Error: Could not set the number of stop bits."
			<< std::endl;
		exit(1);
	}
	//
	// Turn off hardware flow control.
	//
	serial_port->SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
	if (!serial_port-->good())
	{
		std::cout << "Error: Could not use hardware flow control."
			<< std::endl;
		exit(1);
	}
	//
	// Do not skip whitespace characters while reading from the
	// serial port.
	//
	// serial_port.unsetf( std::ios_base::skipws ) ;
	//
	// Wait for some data to be available at the serial port.
	//
}



Communication::~Communication()
{
	SerialStream->Close();
	delete SerialStream;
}

void Communication::checkAndAcquireData(int &route, int &num)
{
	route = busRoute;
	num = numStopsAway;
	if (serial_port->rdbuf()->in_avail() > 0)
	{
		char first_byte; 
		serial_port->get(first_byte);
		if (first_byte != DATA_CMD)
		{
			return;
		}
		//Data format: AxxxBxxN
		string busNum = "";
		char t;
		do
		{
			serial_port->get(t);
			busNum += t;
		} while (t != 'B');
		
		string stopAway = "";
		do
		{
			serial_port->get(t);
			stopAway += t;
		} while (t != 'N');

		//flush the rest of the data
		while (serial_port->rdbuf()->in_avail() > 0)
		{
			char x;
			serial_port->get(x);
		}

		if (isdigit(stopAway) && isdigit(busNum))
		{
			busRoute = stoi(busNum);
			numStopsAway = stoi(stopAway);
			route = busRoute;
			num = numStopsAway;
		}

	}
	return;
}
