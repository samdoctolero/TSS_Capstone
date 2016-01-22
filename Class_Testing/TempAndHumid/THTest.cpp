#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "TempHumid.h" 
#include <wiringPi.h>
#include <unistd.h>

using namespace std;

int main()
{
	wiringPiSetup();
	TempHumid DHT22(1);
	int i;

	while (true)
	{
		double T, H;
		DHT22.PassTempAndHumid(T, H);
		cout << "Count: " << i++ << endl;
		cout << "Temperature is: " << T << endl;
		cout << "Relative Humidity is: " << H<<endl;
		delay(1000);
	}

	return 0;
}