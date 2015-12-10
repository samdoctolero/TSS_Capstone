#pragma once
class atcon : public libxbee::ConCallback {
public:
	explicit atcon(libxbee::XBee &parent, std::string type, struct xbee_conAddress *address = NULL) :
		libxbee::ConCallback(parent, type, address),
		node_detect_complete(true) { };

	void xbee_conCallback(libxbee::Pkt **pkt);

	void start_node_detect(void);
	bool node_detect_complete;
	std::list<remotenode> node_list;
};