#include <iostream>
#include "Solar.h"

using namespace std;

int main()
{
	Solar s(9600);
	s.updateData();
	cout << "End of program..." << endl;
	return 0;
}