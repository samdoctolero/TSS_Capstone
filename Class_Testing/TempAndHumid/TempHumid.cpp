#include "TempHumid.h"
#include <cmath>
#include <wiringPi.h>

#define _2SEC	2.25*1000000 //2 seconds in microseconds

TempHumid::TempHumid(int pin)
:Temperature(0), RelHumidity(0), startTime(0), dataPin(pin)
}


TempHumid::~TempHumid()
{
}


void TempHumid::initStartTime()
{
	this->startTime = micros();
}

bool TempHumid::IsPaused()
{
	if (micros() - this->startTime) <= _2SEC)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int TempHumid::binary2decimal(uint16_t bin)
{
	int decimal = 0;
	for (int i = 0; bin != 0; i++)
	{
		int rem = n % 10;
		bin /= 10;
		decimal += rem*pow(2, i);
	}
	return decimal;
}

void TempHumid::PassTempAndHumid(double &temp, double &rHum)
{
	temp = this->Temperature;
	rHum = this->RelHumidity;
	if (this->IsPaused)
	{
		return;
	}
	else
	{
		int pin = this->dataPin;
		pinMode(pin, INPUT);
		if (digitalRead(pin) == 1) //If the dataPin is high then the pin is free to use
		{
			
			pinMode(pin, OUTPUT);//Set the pin to output to command the sensor
			digitalWrite(pin, 0); //Pull low for 5ms
			delay(5); //pause for 5 milliseconds
			digialWrite(pin, 1); //Pull High then wait for the sensor to pull the pin low
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
					int _t = micros();
					while (digitalRead(pin) == 1){};
					sensor_byte <<= 1; //Shift left by 1
					if (micros() - _t >= 30) //If HIGH took longer than 30us then put 1 at the end of the byte
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

			this->initStartTime();//Initialize pause time start
			//Checksum
			if (((sensor_data[0] + sensor_data[1] + sensor_data[2] + sensor_data[3]) & 0xff) != sensor_data[4])
			{
				return; //If checksum is invalid then just return the built in temp and humidity
			}
			uint16_t humidity = (sensor_data[0] << 8) + sensor_data[1];
			uint16_t temperature = (sensor_data[2] << 8) + sensor_data[3];

			rHum = binary2decimal(humidity) / 10;
			temp = binary2decimal(humidity) / 10;
			this->RelHumidity = rHum;
			this->Temperature = temp;
		}
		else //if the dataPin is occuppied just return the built-in temp and humidity
		{
			return;
		}
	}
	return;
}