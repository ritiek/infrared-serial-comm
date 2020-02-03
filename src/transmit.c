#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "util/util.h"

/* Transfer Specification
    start transmission with the 1st bit that is 1.

    gap to next bit:
    * 80ms => 0
    * 120ms => 1
    * 160ms => character break
    * 200ms => transfer completed

    The LED must be HIGH for 30ms for each signal
*/

void emit_signal(int pin, int duration) {
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
}

void emit_bit(int bit, int pin) {
    switch (bit) {
        case 0:
            delay(80);
            break;
        case 1:
            delay(120);
            break;
    }
    emit_signal(pin, 30);
}

void emit_character(int decimal, int pin) {
    int digit;
    int binary = decimal_to_binary(decimal);
    printf("%c - %d\n", decimal, binary);
    int length = number_digits_length(binary);
    int n_base = positive_power(10, length-1);
    do {
        digit = (binary / n_base) % 10;
        emit_bit(digit, pin);
    }
    while (n_base /= 10);
    delay(160);
    emit_signal(pin, 20);
}

void emit_string(char string[], int pin) {
    int i = 0;
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

    int pin = atoi(argv[1]);
    pinMode(pin, OUTPUT);

    if (argc > 2) {
        for (int i=2; i<argc-1; i++) {
            emit_string(argv[i], pin);
            emit_character(' ', pin);
        }
        emit_string(argv[argc-1], pin);
    } else {
        char c;
        while ((c = getchar()) != 255) {
            emit_character(c, pin);
        }
    }

    // Signal a completed transfer session
    delay(200);
    emit_signal(pin, 20);

    return 0;
}