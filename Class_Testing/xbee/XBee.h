#pragma once
#include <xbee.h>
#include <string>

class XBee
{
private:
	struct xbee * xbee;
	struct xbee_con * prevCon;
	struct xbee_con * nextCon;
	struct xbee_conSettings settings;
	xbee_err ret;
	struct xbee_pkt *pkt;
public:
	xbee_conAddress  prevShelter;
	xbee_conAddress  nextShelter;
	XBee();
	~XBee();
	bool init();

	//this is for testing
	void sendData(std::string msg);
	void dispData();
	//void myCB(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data);


};

