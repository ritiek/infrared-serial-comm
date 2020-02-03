ARMGNU ?= gcc
ARGS ?= -Wall

all : bin/transmit bin/receive

clean :
	rm bin/transmit
	rm bin/receive
	rm -r bin

bin/transmit : src/transmit.c
	mkdir -p bin
	$(ARMGNU) $(ARGS) -lwiringPi -o bin/transmit src/transmit.c

bin/receive : src/receive.c
	mkdir -p bin
	$(ARMGNU) $(ARGS) -lwiringPi -o bin/receive src/receive.c
