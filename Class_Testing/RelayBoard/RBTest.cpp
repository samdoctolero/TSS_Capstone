#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "RelayBoard.h" 

using namespace std;

int main()
{
	RelayBoard RB(0, 1, 101.11, 55.5);
	int gnd, cntl;
	double idleT,minT;
	RB.getPins(cntl,gnd);
	RB.getTemps(idleT, minT);

	cout << "Ground: " << gnd << endl;
	cout << "Control: " << cntl << endl;
	cout << "Idle Temperature: " << idleT << endl;
	cout << "Minimum Temperature: " << minT << endl;

	return 0;
}