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

int receive_character_binary(int pin) {
	struct timeval last_bit;
	struct timeval now;
	float elapsed;

    int value = 1;
    while (value) {
        value = digitalRead(pin);
    }
    int value_old = value;
    int binary = 1;

    gettimeofday(&last_bit, 0);
    while (1) {
        if (value != value_old) {
            gettimeofday(&now, 0);
            elapsed = timedifference_msec(last_bit, now);

            if (elapsed > 400.0f) {
                break;
            } else if (elapsed > 300.0f) {
                // character break
            } else if (elapsed > 200.0f) {
                binary *= 10;
                ++binary;
            } else if (elapsed > 100.0f) {
                binary *= 10;
            }

            last_bit = now;
        }
        value_old = value;
        value = digitalRead(pin);
    }

    return binary;
}

int main() {
    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed !\n");
        return 1;
    }

    int pin = 4;
    pinMode(pin, INPUT);

    int binary = receive_character_binary(pin);
    int decimal = binary_to_decimal(binary);
    printf("%c\n", decimal);

    return 0;
}
