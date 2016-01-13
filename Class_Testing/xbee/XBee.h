#pragma once
#include <xbee.h>

class XBee
{
private:
	struct xbee * xbee;
	struct xbee_con * con;
	struct xbee_conSettings settings;
	xbee_err ret;
public:
	xbee_conAddress  address;
	XBee();
	~XBee();
	bool init();

};

