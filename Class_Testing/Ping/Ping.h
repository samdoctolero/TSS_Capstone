#pragma once
class Ping
{
private:
	int controlPin;
	double dist_tolerance, distance; //in cm
	double runTime;		//runTime is the maximum amount of time the system will run when an object or person is detected
						//default at 5min
	double startTime; //Start time indicates when the object is detected locally
	bool pausedState; //Internal boolean paused state

	void updateDistance(); //update the current distance
	void initStartTime();

public:
	Ping(int control, double tol, double runT);
	~Ping();

	//METHODS or FUNCTIONS:
	void setControlPin( int control); //set the GPIO pins
	void setTolerance(double dist); //set distance tolerance or threshold
	unsigned int getControlPin(); //grab the pin numbers
	double getTolerance(); // grab distance tolerance or threshold
	bool ObjectDetected();
	double getDistance();
};

