ARMGNU ?= gcc
ARGS ?= -lwiringPi -Wall
OPTIMIZATIONS ?= -O2

SOURCE = src
TESTS = tests
BIN = bin

all : $(BIN)/transmit-ir $(BIN)/receive-ir

clean :
	rm -f $(BIN)/transmit-ir
	rm -f $(BIN)/receive-ir
	rm -f $(TESTS)/$(BIN)/test_runner

test :
	mkdir -p $(TESTS)/$(BIN)
	$(ARMGNU) $(ARGS) -o $(TESTS)/$(BIN)/test_runner \
		$(TESTS)/test_runner.c \
		$(SOURCE)/util/util.c \
		$(TESTS)/util/test_util.c
	./$(TESTS)/$(BIN)/test_runner

$(BIN)/transmit-ir : $(SOURCE)/transmit.c
	mkdir -p $(BIN)
	$(ARMGNU) \
	$(SOURCE)/transmit.c \
	$(SOURCE)/util/util.c \
	$(ARGS) $(OPTIMIZATIONS) -o $(BIN)/transmit-ir

$(BIN)/receive-ir : $(SOURCE)/receive.c
	mkdir -p $(BIN)
	$(ARMGNU) \
	$(SOURCE)/receive.c \
	$(SOURCE)/util/util.c \
	$(ARGS) $(OPTIMIZATIONS) -o $(BIN)/receive-ir
