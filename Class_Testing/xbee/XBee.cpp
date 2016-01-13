#include "XBee.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <xbee.h>

XBee::XBee()
{
	memset(&address, 0, sizeof(address));
	address.addr64_enabled = 1;
	address.addr64[0] = 0x00;
	address.addr64[1] = 0x00;
	address.addr64[2] = 0x00;
	address.addr64[3] = 0x00;
	address.addr64[4] = 0x00;
	address.addr64[5] = 0x00;
	address.addr64[6] = 0xFF;
	address.addr64[7] = 0xFF;

}

XBee::~XBee()
{
}

bool XBee::init()
{
	if (xbee_setup(&xbee, "xbee1", "/dev/ttyUSB0", 9600) != 0)
	{
		return false;
	}
	return true;
}
