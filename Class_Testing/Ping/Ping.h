#pragma once
class Ping
{
private:
	int GND_pin, PWR_pin, CONTROL_pin;
	double dist_tolerance, distance; //in cm

public:
	int accumTime;
	Ping(int gnd, int pwr, int control, double tol);
	~Ping();

	//METHODS or FUNCTIONS:
	void setPins(int gnd, int pwr, int control); //set the GPIO pins
	void setTolerance(double dist); //set distance tolerance or threshold
	void getPins(int &gnd, int &pwr, int &control); //grab the pin numbers
	double getTolerance(); // grab distance tolerance or threshold
	void updateDistance(); //update the current distance
	bool ObjectDetected();
};

