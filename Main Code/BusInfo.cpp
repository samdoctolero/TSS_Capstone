#include "BusInfo.h"
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

BusInfo::BusInfo(int num, string ID)
:busNum(num), numStopAway(0), timestamp(0), shelterId(ID)
{
	char currentPath[FILENAME_MAX];
	getcwd(currentPath, FILENAME_MAX);
	currFolder = string(currentPath);
	currFolder.append("/b");
	stringstream ss;
	ss << num;
	currFolder = currFolder + ss.str() + string(".txt");
}

BusInfo::~BusInfo()
{}

void BusInfo::updateData()
{
	ifstream file(currFolder.c_str());
	string line;
	if (file.good())
	{
		getline(file,line); //read bus number
		if (busNum != atoi(line.c_str()))
		{
			cout<<"Error. File corrupted. Read bus number: "<<atoi(line.c_str())<<endl;
			file.close();
			return;
		}
		getline(file, line); //shelter id
        if (atoi(shelterId.c_str()) != atoi(line.c_str()))
		{
            cout << "Error. Not from the correct shelter. Expected: " << shelterId << ". Read: " << line << endl;
			file.close();
			return;
        }
		getline(file, line); //number of stops away
		numStopAway = atoi(line.c_str());
		getline(file, line); //epoch timestamp
		timestamp = atoi(line.c_str());

	}
	file.close();
}

int BusInfo::getNumStopAway()
{
	return numStopAway;
}

int BusInfo::getTimestamp()
{
	return timestamp;
}

string BusInfo::getShelterID()
{
	return shelterId;
}

int BusInfo::getBusNum()
{
	return busNum;
}

