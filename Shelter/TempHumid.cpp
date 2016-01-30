#include "TempHumid.h"
#include <cmath>
#include <wiringPi.h>
#include <//stdint.h>

#include <iostream>

#define _PAUSE_SEC	3000000 //3 seconds in microseconds

TempHumid::TempHumid(int pin)
:Temperature(0), RelHumidity(0), startTime(0), dataPin(pin)
{
	while ((Read()) == -1)
	{
		delay(2500); //If it errors out repeat the process again after a pause
	}
	////std::cout << "Created instance..." << //std::endl;
}


TempHumid::~TempHumid()
{
}


void TempHumid::initStartTime()
{
	startTime = micros();
}

bool TempHumid::IsPaused()
{
	if (std::abs(micros() - startTime) <= _PAUSE_SEC)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int TempHumid::binary2decimal(int bin)
{
	int decimal = 0;
	for (int i = 0; bin != 0; i++)
	{
		int rem = bin % 10;
		bin /= 10;
		decimal += rem*pow(2, i);
	}
	return decimal;
}

int TempHumid::Read()
{

	int pin = dataPin;
	pinMode(pin, INPUT);
	if (digitalRead(pin) == 1) //If the dataPin is high then the pin is free to use
	{
		//std::cout << "Ready to read data..." << //std::endl;
		pinMode(pin, OUTPUT);//Set the pin to output to command the sensor
		digitalWrite(pin, 0); //Pull low for 5ms
		delay(10); //pause for 10 milliseconds
		digitalWrite(pin, 1); //Pull High then wait for the sensor to pull the pin low
		pinMode(pin, INPUT);
		while (digitalRead(pin) == 1){}
		while (digitalRead(pin) == 0){}
		while (digitalRead(pin) == 1){}
		//After the "while" sequence, data transmission starts
		uint8_t sensor_data[5] = { 0 };
		for (int i = 0; i < 5; i++)
		{
			uint8_t sensor_byte = 0;
			for (int j = 1; j <= 8; j++)
			{
				while (digitalRead(pin) == 0){}
				int _t = 0;
				while (digitalRead(pin) == 1)
				{
					delayMicroseconds(2);
					//////std::cout << "While 5 Clear " << i << " " << j << //std::endl;
					_t+=2;
					if (_t > 100) //An Error has occured just return the previous value
					{
						//std::cout << "Error" << //std::endl;
						initStartTime();//Initialize pause time start
						return -1;
					}
				}
				sensor_byte <<= 1; //Shift left by 1
				if (_t > 30) //If HIGH took longer than 30us then put 1 at the end of the byte
				{
					sensor_byte |= 1;
				}
				else //if the HIGH took less than 30us then put 0 at the end of the byte
				{
					sensor_byte |= 0;
				}
			}
			sensor_data[i] = sensor_byte;
		}

		initStartTime();//Initialize pause time start
		//Checksum
		if (((sensor_data[0] + sensor_data[1] + sensor_data[2] + sensor_data[3]) & 0xff) != sensor_data[4])
		{
			////std::cout << "Invalid checksum" << //std::endl;
			return 0; //If checksum is invalid then just return the built in temp and humidity
		}
		int humidity = (sensor_data[0] << 8) + sensor_data[1];
		int temperature = (sensor_data[2] << 8) + sensor_data[3];
		RelHumidity = ((double)humidity) / 10;
		Temperature = ((double)temperature) / 10;
		////std::cout << "Got temperature" << //std::endl;
	}
	else //if the dataPin is occuppied just return the built-in temp and humidity
	{
		//std::cout << "Pin Busy" << //std::endl;
		return 0;
	}
	return 0;
}

void TempHumid::PassTempAndHumid(double &temp, double &rHum)
{
	temp = Temperature;
	rHum = RelHumidity;
	if (IsPaused())
	{
		//std::cout << "Paused" << //std::endl;
		return;
	}
	else
	{

		while ((Read()) == -1)
		{
			delay(2500);//If it errors out repeat the process again after a pause
		}
		temp = Temperature;
		rHum = RelHumidity;
	}
	return;
}