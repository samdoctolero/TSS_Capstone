#pragma once
class RelayBoard
{
private:
	int controlPin, groundPin, bulbState;
	double idleTemp,minTemp;
	//send to the relay a number
	void sendToRelay(int state);
public:
	enum
	{
		OFF = 0,
		IDLE = 1,
		MAX = 2
	};

	RelayBoard(int control,int ground, double idleT,double minT);
	~RelayBoard();
	//Getter and setter
	void setPins(int control, int ground);
	void getPins(int &control, int &ground);
	void getTemps(double &idleT, double &minT);
	//Control
	void heatControl(double bulbTemp, double envTemp, bool objectPresent);
};

