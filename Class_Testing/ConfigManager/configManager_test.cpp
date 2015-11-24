#include <iostream>
#include <string>
#inculde "ConfigManager.h"

using namespace std;

int main()
{
	ConfigManager config;

	cout << "Ping ground:" << config.ping_ground << "\n";
	cout << "Bus Nmber: " << config.bus.number << "\n";

	return 0;
}