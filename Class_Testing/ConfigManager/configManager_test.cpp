#include <iostream>
#include <string>
#include "ConfigManager.h"

using namespace std;

int main()
{
	ConfigManager c();

	cout << "Ping ground:" << c->ping_ground << "\n";
	cout << "Bus Nmber: " << c->bus[1].number << "\n";

	return 0;
}