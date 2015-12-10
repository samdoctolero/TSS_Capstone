#include <stdint.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <list>
#include <iomanip>

#include <xbee.h>
#include "remotenode.h"
#include "atcon.h"

int main(int argc, char *argv[]) {
	int i;

	try {
		/* setup libxbee */
		libxbee::XBee xbee("xbee1", "/dev/ttyUSB0", 57600);

		/* make a connection */
		atcon con(xbee, "Local AT"); /* AT connection with a callback handler */

									 /* start node detect */
		con.start_node_detect();

		/* lazy-wait for it to finish */
		while (!con.node_detect_complete) {
			usleep(100000);
		}

		/* print out a list of nodes */
		for (std::list<remotenode>::iterator n = con.node_list.begin(); n != con.node_list.end(); n++) {
			/* it's just easier to print nice-looking output using printf()... */
			printf("Node: %-20s  0x%04X  0x%08X 0x%08X\n",
				n->getName().c_str(), n->getAddr16(), n->getAddr64Hi(), n->getAddr64Lo());
		}

	}
	catch (xbee_err err) {
		std::cout << "Error " << err << "\n";
	}

	return 0;
}
