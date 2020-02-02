#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

float timedifference_msec(struct timeval t0, struct timeval t1)  {
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

int number_digits_length(int number) {
    int digits = 0;
    while (number) {
        number /= 10;
        ++digits;
    }
    return digits;
}

int positive_power(int base, int n) {
    if (n < 1) {
        return 1;
    }
    int result = base;
    while (--n) {
        result *= base;
    }
    return result;
}

int binary_to_decimal(int binary) {
    int digit;
    int decimal = 0;
    int length = number_digits_length(binary);
    int n_base = positive_power(10, --length);
    int max_bit_to_decimal = positive_power(2, length);
    do {
        digit = (binary / n_base) % 10;
        decimal += digit * max_bit_to_decimal;
        max_bit_to_decimal /= 2;
    }
    while (n_base /= 10);
    return decimal;
}

int receive_data(char string[], int pin) {
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
            // printf("elapsed for below bit: %d\n", elapsed);

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

int main() {
    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed !\n");
        return 1;
    }

    int pin = 4;
    pinMode(pin, INPUT);

    char string[1000];
    receive_data(string, pin);
    printf("%s\n", string);

    return 0;
}
