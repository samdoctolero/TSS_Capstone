#include <wiringPi.h> //Need to be installed on the Pi to be used
#include <wiringPiI2C.h>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "IR.h"

#define ID 0x40

IR::IR()
{
	if ((FD = wiringPiI2CSetup(ID)) < 0)
	{
		std::cout << "Error. Cannot initialize i2c" << std::endl;
	}
}

IR::~IR()
{
}

double IR::readTemp()
{
	int test = wiringPiI2CRead(this->FD);
	std::cout << test << std::endl;
	return 0;
}
