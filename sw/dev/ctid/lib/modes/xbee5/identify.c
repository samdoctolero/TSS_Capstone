/*
	libxbee - a C library to aid the use of Digi's XBee wireless modules
	          running in API mode.

	Copyright (C) 2009 onwards  Attie Grande (attie@attie.co.uk)

	libxbee is free software: you can redistribute it and/or modify it
	under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	libxbee is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../internal.h"
#include "../../xbee_int.h"
#include "../../mode.h"
#include "../../pkt.h"
#include "../common.h"
#include "identify.h"

xbee_err xbee_s5_identify_rx_func(struct xbee *xbee, void *arg, unsigned char identifier, struct xbee_buf *buf, struct xbee_frameInfo *frameInfo, struct xbee_conAddress *address, struct xbee_pkt **pkt) {
	struct xbee_pkt *iPkt;
	xbee_err ret;
	struct xbee_conAddress *addr;

	if (!xbee || !frameInfo || !buf || !address || !pkt) return XBEE_EMISSINGPARAM;
	
	if (buf->len < 30) return XBEE_ELENGTH;
	
	if ((ret = xbee_pktAlloc(&iPkt, NULL, buf->len - 12)) != XBEE_ENONE) return ret;
	
	iPkt->options = buf->data[11];
	
	iPkt->dataLen = buf->len - 12;
	if (iPkt->dataLen > 0) {
		memcpy(iPkt->data, &(buf->data[12]), iPkt->dataLen);
		
		if (iPkt->dataLen > 10) {
			xbee_pktDataAdd(iPkt, "Address (64-bit)", 0, &(iPkt->data[2]), NULL);
			
			if ((addr = malloc(sizeof(*addr))) != NULL) {
				memset(addr, 0, sizeof(*addr));
				addr->addr64_enabled = 1;
				memcpy(addr->addr64, &(iPkt->data[2]), 8);
				
				if (xbee_pktDataAdd(iPkt, "Address", 0, addr, free) != XBEE_ENONE) {
					free(addr);
				}
			}
		}
		
		if (iPkt->dataLen > 11) {
			/* just point into the packet data */
			xbee_pktDataAdd(iPkt, "NI", 0, &(iPkt->data[10]), NULL);
		}
	}
	iPkt->data[iPkt->dataLen] = '\0';
	
	*pkt = iPkt;
	
	return XBEE_ENONE;
}

/* ######################################################################### */

void xbee_s5_identify_init(struct xbee_modeConType *conType) {
	/* we REALLY have to babysit Windows... */
	conType->allowFrameId = 0;
	conType->useTimeout = 0;
	conType->addressRules = ADDR_NONE;
	conType->rxHandler->identifier = 0x95;
	conType->rxHandler->func = xbee_s5_identify_rx_func;
}
struct xbee_modeDataHandlerRx xbee_s5_identify_rx;
struct xbee_modeConType xbee_s5_identify = { "Identify", &xbee_s5_identify_rx, NULL, xbee_s5_identify_init };
