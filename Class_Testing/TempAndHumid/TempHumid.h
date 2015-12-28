#pragma once
class TempHumid
{
private:
	double Temperature, RelHumidity; //Built in stored temperature and humidity
	int startTime, dataPin; //startTime for when the module needs to be paused for  at least 2 seconds every after data transmission
							//dataPin is the pin on the GPIO that will be used for data transmission

	void initStartTime(); //Initializes the starTime
	bool IsPaused();	//
	int binary2decimal(uint16_t bin); //binary to decimal conversion

public:
	TempHumid(int pin); //constructor
	~TempHumid(); //destructor

	void PassTempAndHumid(double &temp, double &rHum); //Gives the temperature and humidity by pass by reference
};