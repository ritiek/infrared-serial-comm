#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "util/util.h"

void emit_signal(unsigned int pin, unsigned int duration) {
    /// Sets the GPIO pin to HIGH for given duration.
    digitalWrite(pin, HIGH);
    ms_sleep(duration);
    digitalWrite(pin, LOW);
}

void emit_bit(unsigned int bit, unsigned int pin) {
    /// Waits an appropriate time before sending
    /// a signal so that the receiver on other side
    /// can identify the bit (0 or 1).
    switch (bit) {
        case 0:
            ms_sleep(BIT0BREAK);
            break;
        case 1:
            ms_sleep(BIT1BREAK);
            break;
    }
    emit_signal(pin, LEDHIGH);
}

void emit_character(unsigned int decimal, unsigned int pin) {
    /// Takes in an ASCII decimal and transmits
    /// it as binary, bit-by-bit through the GPIO pin.
    unsigned int digit;
    unsigned int binary = decimal_to_binary(decimal);
    printf("%c - %d\n", decimal, binary);
    unsigned int length = number_digits_length(binary);
    unsigned int n_base = positive_power(10, length-1);
    do {
        digit = (binary / n_base) % 10;
        emit_bit(digit, pin);
    }
    while (n_base /= 10);
    // Signal a character break so the receiver
    // can attempt to parse the received bits
    ms_sleep(CHARBREAK);
    emit_signal(pin, LEDHIGH);
}

void emit_string(char string[], unsigned int pin) {
    /// Takes in a character array and transmits
    /// each character through the GPIO pin.
    unsigned int i = 0;
    while (string[i]) {
        emit_character(string[i++], pin);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <led-gpio-pin-number> [string] [string] [...]\n", argv[0]);
        return -1;
    }

    if (wiringPiSetup() == -1) {
        fprintf(stderr, "setup wiringPi failed!\n");
        return 1;
    }

    unsigned int pin = atoi(argv[1]);
    pinMode(pin, OUTPUT);

    if (argc > 2) {
        // Read input from command-line arguments
        for (unsigned int i=2; i<argc-1; i++) {
            emit_string(argv[i], pin);
            emit_character(' ', pin);
        }
        emit_string(argv[argc-1], pin);
    } else {
        // Read input from stdin
        char c;
        while ((c = getchar()) != 255) {
            emit_character(c, pin);
        }
    }

    // Signal a completed transmission session
    ms_sleep(TRANSFERBREAK);
    emit_signal(pin, LEDHIGH);

    return 0;
}
