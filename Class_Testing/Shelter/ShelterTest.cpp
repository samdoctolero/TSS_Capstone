#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "Shelter.h" 

using namespace std;

int main()
{
	Shelter S;
	S.initialize();
	S.mainLoop();
	return 0;
}