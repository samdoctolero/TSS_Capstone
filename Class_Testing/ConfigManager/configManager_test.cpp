#include <iostream>
#include <string>
#include "ConfigManager.h"

using namespace std;

int main()
{
	ConfigManager config;

	cout << "Ping ground:" << config.ping_ground << "\n";
	cout << "Bus Nmber: " << config.bus.number << "\n";

	return 0;
}