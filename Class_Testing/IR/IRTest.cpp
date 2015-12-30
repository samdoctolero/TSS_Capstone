#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "IR.h" 

using namespace std;

int main()
{
	IR bulbT(); //Control pin = 15, and tolerance = 2 meters (since PING can only operate within 3m)
	bulbT.readTemp();
	return 0;
}