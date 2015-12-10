PROG?=main

all: $(PROG)

run: all
	LD_LIBRARY_PATH=../../xbee3/lib ./$(PROG)

new: clean all

clean:
	-rm $(PROG)

$(PROG): $(PROG).cpp remotenode.cpp ../../xbee3/lib/libxbee.so ../../xbee3/lib/libxbeep.so
	g++ $(filter %.cpp,$^) -g -o $@ -I ../../xbee3 -L ../../xbee3/lib -lxbeep -lxbee -lpthread -lrt
