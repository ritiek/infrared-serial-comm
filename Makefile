ARMGNU ?= gcc
ARGS ?= -Wall

all : bin/transmit-ir bin/receive-ir

clean :
	rm bin/transmit-ir
	rm bin/receive-ir
	rm -r bin

bin/transmit-ir : src/transmit.c
	mkdir -p bin
	$(ARMGNU) $(ARGS) -lwiringPi -o bin/transmit-ir src/transmit.c

bin/receive-ir : src/receive.c
	mkdir -p bin
	$(ARMGNU) $(ARGS) -lwiringPi -o bin/receive-ir src/receive.c
