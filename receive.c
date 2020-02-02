#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

float timedifference_msec(struct timeval t0, struct timeval t1)  {
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

int main() {
	struct timeval last_bit;
	struct timeval now;
	float elapsed;

    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed !\n");
        return 1;
    }

    int pin = 4;
    pinMode(pin, INPUT);

    char binary[100] = "1";
    char bit[2] = "1";

    int value = 1;

    while (value) {
        value = digitalRead(pin);
    }
    int value_old = value;

    gettimeofday(&last_bit, 0);
    while (1) {
        if (value != value_old) {
            gettimeofday(&now, 0);
            elapsed = timedifference_msec(last_bit, now);
            // printf("%f\n", elapsed);

            if (elapsed > 400.0f) {
                break;
            } else if (elapsed > 300.0f) {
                strcpy(bit, " ");
                strcat(binary, bit);
            } else if (elapsed > 200.0f) {
                strcpy(bit, "1");
                strcat(binary, bit);
            } else if (elapsed > 100.0f) {
                strcpy(bit, "0");
                strcat(binary, bit);
            }

            // printf("%s\n", binary);
            last_bit = now;
        }
        value_old = value;
        value = digitalRead(pin);

    }
    printf("%s\n", binary);
    return 0;
}
