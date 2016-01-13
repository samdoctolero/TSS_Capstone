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
		cout << "Error. Cannot connect to XBee device" << endl;
	}
	return 0;
}