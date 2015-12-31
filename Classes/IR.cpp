#include <wiringPi.h> //Need to be installed on the Pi to be used
#include <wiringPiI2C.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "IR.h"

#define ID 0x40
#define TMP006_MANID 0xFE
#define TMP006_DEVID 0xFF

#define TMP006_CONFIG     0x02

#define TMP006_CFG_RESET    0x8000
#define TMP006_CFG_MODEON   0x7000
#define TMP006_CFG_1SAMPLE  0x0000
#define TMP006_CFG_2SAMPLE  0x0200
#define TMP006_CFG_4SAMPLE  0x0400
#define TMP006_CFG_8SAMPLE  0x0600
#define TMP006_CFG_16SAMPLE 0x0800
#define TMP006_CFG_DRDYEN   0x0100
#define TMP006_CFG_DRDY     0x0080

#define TMP006_B0 -0.0000294
#define TMP006_B1 -0.00000057
#define TMP006_B2 0.00000000463
#define TMP006_C2 13.4
#define TMP006_TREF 298.15
#define TMP006_A2 -0.00001678
#define TMP006_A1 0.00175
#define TMP006_S0 6.4  // * 10^-14

#define TMP006_VOBJ  0x00
#define TMP006_TAMB	 0x01

IR::IR()
{
	if ((FD = wiringPiI2CSetup(ID)) < 0)
	{
		std::cout << "Error. Cannot initialize i2c" << std::endl;
	}
	else
	{
		this->config_sensor(this->FD, TMP006_CFG_16SAMPLE); //default setting
		int16_t mid = read16(this->FD, TMP006_MANID);
		int16_t did = read16(this->FD, TMP006_DEVID);
		if ((mid != 0x5449) || (did != 0x67))
		{
			std::cout << "Error. Wrong IDs" << std::endl;
			printf("ManID: %X\nDevID: %x\n", mid, did);
		}
	}
}

IR::~IR()
{
}

int16_t IR::read16(unsigned int addr, unsigned int reg)
{
	int16_t raw1 = wiringPiI2CReadReg16(addr, reg);
	//raw = 0x0000FFFF & raw;
	/*int16_t r = raw;
	int16_t r1 = (r >> 8);
	int16_t r2 = (raw << 8);
	raw = (r1 | r2);*/

	unsigned int raw = 0x0000FFFF & raw1;
	//printf("VRaw: 0x%X\n", raw);
	unsigned int r = raw;
	unsigned int r1 = (r >> 8);

	//printf("R1: 0x%X\n", r1);
	unsigned int r2 = (raw << 8);

	//printf("R2: 0x%X\n", r2);
	raw = (r1 + r2);

	return raw;
}

void IR::config_sensor(unsigned int addr, unsigned int samples)
{
	wiringPiI2CWriteReg16(this->FD, addr, samples);
}

int16_t IR::readRawDieTemperature(unsigned int addr)
{
	int16_t raw = read16(addr, TMP006_TAMB);
	raw >>= 2;
	return raw;
}

int16_t IR::readRawVoltage(unsigned int addr)
{
	int16_t raw = read16(addr, TMP006_VOBJ);
	
	return raw;
}

double IR::readObjTemp()
{
	double Tdie = readRawDieTemperature(this->FD);
	double Vobj = readRawVoltage(this->FD);

	Vobj *= 156.25;  // 156.25 nV per LSB
	Vobj /= 1000; // nV -> uV
	Vobj /= 1000; // uV -> mV
	Vobj /= 1000; // mV -> V
	Tdie *= 0.03125; // convert to celsius
	Tdie += 273.15; // convert to kelvin

	// Equations for calculating temperature found in section 5.1 in the user guide
	double tdie_tref = Tdie - TMP006_TREF;
	double S = (1 + TMP006_A1*tdie_tref +
		TMP006_A2*tdie_tref*tdie_tref);
	S *= TMP006_S0;
	S /= 10000000;
	S /= 10000000;

	double Vos = TMP006_B0 + TMP006_B1*tdie_tref +
		TMP006_B2*tdie_tref*tdie_tref;

	double fVobj = (Vobj - Vos) + TMP006_C2*(Vobj - Vos)*(Vobj - Vos);

	double Tobj = sqrt(sqrt(Tdie * Tdie * Tdie * Tdie + fVobj / S));

	Tobj -= 273.15; // Kelvin -> *C

	return Tobj;
}

double IR::readDieTemp()
{
	double Tdie = readRawDieTemperature(this->FD);
	Tdie *= 0.03125; // convert to celsius
	return Tdie;
}