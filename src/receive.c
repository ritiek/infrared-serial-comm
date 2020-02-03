#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "util/util.h"

void receive_data(char string[], int pin) {
    struct timeval last_signal;
    struct timeval now;
    int decimal;
    float elapsed;

    int value = 1;
    while (value) {
        value = digitalRead(pin);
    }
    int value_old = value;
    int binary = 1;
    int i = 0;

    gettimeofday(&last_signal, 0);
    while (1) {
        if (value != value_old) {
            gettimeofday(&now, 0);
            elapsed = timedifference_msec(last_signal, now);

            if (elapsed > 200.0f) {
                decimal = binary_to_decimal(binary);
                printf("%c - %d\n", decimal, binary);
                string[i++] = decimal;
                break;
            } else if (elapsed > 160.0f) {
                decimal = binary_to_decimal(binary);
                printf("%c - %d\n", decimal, binary);
                string[i++] = decimal;
                binary = 0;
            } else if (elapsed > 120.0f) {
                binary *= 10;
                ++binary;
            } else if (elapsed > 80.0f) {
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

    int pin = atoi(argv[1]);
    pinMode(pin, INPUT);

    char string[1000];
    receive_data(string, pin);
    printf("%s\n", string);

    return 0;
}