#pragma once
class Shelter
{

#define DEFAULT_NUM_BUS 10
public:
	struct Bus
	{
		int number,			//bus number
		num_stop_away,		//number of stops away from this stop/shelter
		id;				//bus id
		double initial_time;//time since last update for a certain bus
	};
private:
	Ping proximityObj;
	RelayBoard relayObj;
	/*
		Add other objects here (i.e. temperature, xbee...)
	*/
	int shelter_id;		//hex shelter id
	Bus bus[DEFAULT_NUM_BUS];		//busses in one shelter object
public:
	
	Shelter();
	~Shelter();
	void Loop(); //main algorithm
	void readConfig();//read the configuration data from a file -> Do later when all the configuration items have been confirmed
	void processData(); //this where all the data is processed
};

