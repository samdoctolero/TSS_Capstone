#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Communication.h" 
#include <unistd.h>

using namespace std;

int main()
{
	Communication busInfo;
	if (busInfo.init("SR001R010R052P0040P0001M0001X") == true)
	{
		cout << "Initialization complete!" << endl;
	}
	else
	{
		cout << "Initialization failed..." << endl;
	}

	/*
	while (true)
	{
		busInfo.sendMsg("working?");
		cout << busInfo.readMsg() << endl;
	}
	*/
	return 0;
}