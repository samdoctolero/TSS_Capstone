#include "XBee.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <xbee.h>

using namespace std;

XBee::XBee()
{
	memset(&prevShelter, 0, sizeof(prevShelter));
	prevShelter.addr64_enabled = 1;
	prevShelter.addr64[0] = 0x00;
	prevShelter.addr64[1] = 0x00;
	prevShelter.addr64[2] = 0x00;
	prevShelter.addr64[3] = 0x00;
	prevShelter.addr64[4] = 0x00;
	prevShelter.addr64[5] = 0x00;
	prevShelter.addr64[6] = 0xFF;
	prevShelter.addr64[7] = 0xFF;

	/*
	memset(&prevShelter, 0, sizeof(prevShelter));
	prevShelter.addr64_enabled = 1;
	prevShelter.addr64[0] = 0x00;
	prevShelter.addr64[1] = 0x13;
	prevShelter.addr64[2] = 0xA2;
	prevShelter.addr64[3] = 0x00;
	prevShelter.addr64[4] = 0x40;
	prevShelter.addr64[5] = 0xC1;
	prevShelter.addr64[6] = 0xC3;
	prevShelter.addr64[7] = 0xB2;
	*/

}

XBee::~XBee()
{
	//xbee_conEnd(nextCon);
	xbee_conEnd(prevCon);
	xbee_shutdown(xbee);
}

bool XBee::init()
{
	xbee_err ret;
	if ((ret = xbee_setup(&xbee, "xbee1", "/dev/ttyUSB0", 57600)) != XBEE_ENONE)
	{
		printf("ret: %d (%s)\n", ret, xbee_errorToStr(ret));
		printf("Cannot connect to device");
		return false;
	}

	if ((ret = xbee_conNew(xbee, &prevCon, "64-bit I/O", &prevShelter)) != XBEE_ENONE)
	{
		xbee_log(xbee, -1, "xbee_conNew() returned: %d (%s)", ret, xbee_errorToStr(ret));
		cout << "Cannot connect to other xbees" <<endl <<xbee_errorToStr(ret) << endl;
		return false;
	}

	
	struct xbee_conSettings settings;
	xbee_conSettings(prevCon, NULL, &settings);
	//settings.disableAck = 1;
	settings.catchAll = 1;
	xbee_conSettings(prevCon, &settings, NULL);
	
	
	//if (xbee_conNew(xbee, &nextCon, "64-bit Data", &nextShelter) != 0)
	//{
	//	return false;
	//}
	return true;
}

void XBee::sendData(string msg)
{
	xbee_conTx(prevCon, NULL, &msg[0]);
	usleep(10000);
}

void XBee::dispData()
{
	if (((ret = xbee_conRx(prevCon,&pkt,NULL)) != XBEE_ENONE))
	{
		cout << xbee_errorToStr(ret) << endl;
		cout << (pkt)->dataLen << endl;
	}
	else
	{
		cout << (pkt)->data << endl;
		xbee_pktFree(pkt);
	}
}

