#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "modbus.h"

using namespace std;

int main()
{
	modbus_t *ctx;

	/* Set up a new MODBUS context */
	ctx = modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 2);
	if (ctx == NULL) {
		fprintf(stderr, "Unable to create the libmodbus context\n");
		return -1;
	}
}