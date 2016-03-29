#pragma once
class IR
{
private:
	int FD;
	void config_sensor(unsigned int addr, unsigned int samples);
	int16_t readRawDieTemperature(unsigned int addr);
	int16_t readRawVoltage(unsigned int addr);
	int16_t read16(unsigned int addr, unsigned int reg);
public:
	IR();
	~IR();
	double readObjTemp();
	double readDieTemp();
};

