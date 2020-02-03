#include "util.h"

float timedifference_msec(struct timeval t0, struct timeval t1)  {
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
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

int decimal_to_binary(int decimal) {
    int remainder;
    int multiplier = 1;
    int binary = 0;
    while (decimal) {
        remainder = decimal % 2;
        decimal /= 2;
        binary += remainder * multiplier;
        multiplier *= 10;
    }
    return binary;
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

int number_digits_length(int number) {
    int digits = 0;
    while (number) {
        number /= 10;
        ++digits;
    }
    return digits;
}
