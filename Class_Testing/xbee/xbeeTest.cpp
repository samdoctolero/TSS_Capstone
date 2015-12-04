#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <xbee.h>

void myCB(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	if ((*pkt)->dataLen <= 0) return;

	/* tell the observer what we received */
	printf("rx: [%s]\n", (*pkt)->data);

	/* return the message to the other XBee */
	printf("tx: %d\n", xbee_connTx(con, NULL, (*pkt)->data, (*pkt)->dataLen));
}

int main(void) {
	struct xbee *xbee;
	struct xbee_con *con;
	struct xbee_conAddress address;
	unsigned char txRet;
	xbee_err ret;

	/* setup libxbee, using a Series 1 XBee, on /dev/ttyUSB0, at 57600 baud */
	xbee_setup(&xbee, "xbee1", "/dev/ttyUSB0", 57600);

	/* setup a 64-bit address */
	memset(&address, 0, sizeof(address));
	address.addr64_enabled = 1;
	address.addr64[0] = 0x00;
	address.addr64[1] = 0x13;
	address.addr64[2] = 0xA2;
	address.addr64[3] = 0x00;
	address.addr64[4] = 0x40;
	address.addr64[5] = 0x08;
	address.addr64[6] = 0x18;
	address.addr64[7] = 0x26;

	xbee_conNew(xbee, &con, "64-bit Data", &address);

	xbee_conCallbackSet(con, myCB, NULL);

	ret = xbee_conTx(con, &txRet, "NI");

	printf("tx: %d\n", ret);
	printf("txRet: %d\n", txRet);

	usleep(1000000);
	xbee_conEnd(con);

	/* shutdown libxbee */
	xbee_shutdown(xbee);

	printf("Hello World! End!\n");

	return 0;
}