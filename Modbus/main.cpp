#include <iostream>
#include "ModbusMaster232.h"

using namespace std;

int main()
{
	ModbusMaster232 M;
	M.begin(9600);
	int result = M.readHoldingRegisters(15,1);
	cout << result << endl;
	result = M.readCoils(1, 1);
	cout << "Coils: " << result<< endl;
	return 0;
}