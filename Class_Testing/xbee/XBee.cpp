#include "XBee.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <xbee.h>

using namespace std;

void myCB(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	if (this->(*pkt)->dataLen == 0) {
		printf("too short...\n");
		return;
	}
	printf("rx: [%s]\n", this->(*pkt)->data);
}

XBee::XBee()
{
	memset(&prevShelter, 0, sizeof(prevShelter));
	nextShelter.addr16_enabled = 1;
	nextShelter.addr16[0] = 0x00;
	nextShelter.addr16[1] = 0x0A;

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
		return false;
	}

	if (xbee_conNew(xbee, &prevCon, "64-bit Data", &prevShelter) != XBEE_ENONE)
	{
		cout << "Cannot connect to other xbees" << endl;
		return false;
	}

	struct xbee_conSettings settings;
	xbee_conSettings(prevCon, NULL, &settings);
	settings.disableAck = 1;
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
	//xbee_t_conCallback  CB;
	//cout << CB << endl;
	//xbee_err ret;
	//if ((ret = xbee_conCallbackSet(prevCon,CB, NULL)) != XBEE_ENONE) {
		//xbee_log(xbee, -1, "xbee_conCallbackSet() returned: %d", ret);
		//return;
	//}
	//cout << pkt->data << endl;
	//usleep(300000000);
	/*
	string my_info;
	void * p = &my_info;
	if (xbee_conDataGet(prevCon, &p) != 0)
	{
		std::cout << "Could not grab data" << std::endl;
	}
	else
	{
		std::cout << "Valid data: " << my_info << std::endl;
	}
	*/
	//cout << "Here" << endl;

	if ((xbee_conRx(prevCon,pkt,NULL) != XBEE_ENONE))
	{
		fprintf(stderr, "xbee_conRx(): %d - %s\n", ret, xbee_errorToStr(ret));
		exit(1);
	}
	else
	{
		cout << pkt->data << endl;
	}

}

