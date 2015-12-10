#pragma once
class remotenode {
public:
	explicit remotenode(std::string name, uint16_t addr16, uint64_t addr64) :
		name(name),
		addr16(addr16),
		addr64(addr64) { };
	explicit remotenode(std::vector<unsigned char> nd_payload);

	std::string getName(void)     const { return name; }
	uint16_t    getAddr16(void)   const { return addr16; }
	uint64_t    getAddr64(void)   const { return addr64; }
	uint32_t    getAddr64Hi(void) const { return (addr64 >> 32) & 0xFFFFFFFF; }
	uint32_t    getAddr64Lo(void) const { return addr64 & 0xFFFFFFFF; }

private:
	std::string name;
	uint16_t addr16;
	uint64_t addr64;
};

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