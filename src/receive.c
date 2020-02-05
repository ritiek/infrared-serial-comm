#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "util/util.h"

void receive_data(char string[], unsigned int pin) {
    struct timeval last_signal;
    struct timeval now;
    unsigned int decimal;
    float elapsed;

    unsigned int value = 1;
    while (value) {
        value = digitalRead(pin);
    }
    unsigned int value_old = value;
    unsigned int binary = 1;
    unsigned int i = 0;

    gettimeofday(&last_signal, 0);
    while (1) {
        if (value != value_old) {
            gettimeofday(&now, 0);
            elapsed = timedifference_msec(last_signal, now);

            if (elapsed > TRANSFERBREAK) {
                break;
            } else if (elapsed > CHARBREAK) {
                decimal = binary_to_decimal(binary);
                printf("%c - %d\n", decimal, binary);
                string[i++] = decimal;
                binary = 0;
            } else if (elapsed > BIT1BREAK) {
                binary *= 10;
                ++binary;
            } else if (elapsed > BIT0BREAK) {
                binary *= 10;
            }

            last_signal = now;
        }
        value_old = value;
        value = digitalRead(pin);
    }

    string[i] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <receiver-gpio-pin-number>", argv[0]);
        return -1;
    }

    if (wiringPiSetup() == -1) {
        fprintf(stderr, "setup wiringPi failed!\n");
        return 1;
    }

    unsigned int pin = atoi(argv[1]);
    pinMode(pin, INPUT);

    char string[1000];
    receive_data(string, pin);
    printf("%s\n", string);

    return 0;
}
