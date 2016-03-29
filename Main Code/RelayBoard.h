#pragma once
class RelayBoard
{
private:
	int controlPin, bulbState;
	double idleTemp,minEnvTemp;
	//send to the relay a number
	void sendToRelay(int state);
public:
	enum
	{
		OFF = 0,
		IDLE = 1,
		MAX = 2
	};

	RelayBoard(int control, double idleT,double minT);
	~RelayBoard();
	//Getter and setter
	void setControlPin(int control);
	unsigned int getControlPin();
	void getTempSettings(double &idleT, double &minT);
	//Control
	void heatControl(double bulbTemp, double envTemp, bool objectPresent);
};

