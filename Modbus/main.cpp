#include <iostream>
#include "ModbusMaster232.h"

using namespace std;

int main()
{
	ModbusMaster232 M;
	M.begin(9600);
	int result = M.readHoldingRegisters(1,0);
	cout << result << endl;
	return 0;
}