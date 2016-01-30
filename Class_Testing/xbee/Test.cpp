#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "XBee.h" 

using namespace std;

int main()
{
	XBee busInfo;
	if (busInfo.init() == false)
	{
		//cout << "Error. Cannot connect to XBee device" << endl;
		return 0;
	}
	else
	{
		cout << "Connection successful" << endl;
		busInfo.sendData("Hello Arduino. Do you copy?\n");
		
		while (true)
		{
			busInfo.sendData("Hello Arduino. Do you copy?\n");
			busInfo.dispData();
			cout << "In the loop" << endl;
			usleep(1000000);
		}
		
	}
	cout << "Exited loop" << endl;
	return 0;
}