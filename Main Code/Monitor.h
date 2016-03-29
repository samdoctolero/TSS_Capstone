#pragma once
class Monitor
{
private:
	bool hdmiOn;						//keep track of the screen's status
	bool controlEnabled;				//enable screen saver function

	void turnOn();						//turns on the screen
	void turnOff();						//turns off the screen
public:
	Monitor(bool hdmi = true, bool en = true);	//constructor
	~Monitor();									//destructor
	void control(bool obj);						//control algorithm for the screen
};