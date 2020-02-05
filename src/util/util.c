#include "util.h"
#include <unistd.h>

const unsigned int LEDHIGH = 20;
const unsigned int BIT0BREAK = 50;
const unsigned int BIT1BREAK = 70;
const unsigned int CHARBREAK = 90;
const unsigned int TRANSFERBREAK = 110;

void ms_sleep(unsigned int ms) {
    usleep(ms * 1000);
}

float timedifference_msec(struct timeval t0, struct timeval t1)  {
    /// Returns the difference between 2 timevalues in milliseconds.
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

unsigned int binary_to_decimal(unsigned int binary) {
    /// Converts a binary number to its corresponding
    /// decimal notation.
    unsigned int digit;
    unsigned int decimal = 0;
    unsigned int length = number_digits_length(binary);
    unsigned int n_base = positive_power(10, --length);
    unsigned int max_bit_to_decimal = positive_power(2, length);
    do {
        digit = (binary / n_base) % 10;
        decimal += digit * max_bit_to_decimal;
        max_bit_to_decimal /= 2;
    }
    while (n_base /= 10);
    return decimal;
}

unsigned int decimal_to_binary(unsigned int decimal) {
    /// Converts a decimal number to its corresponding
    /// binary notation.
    unsigned int remainder;
    unsigned int multiplier = 1;
    unsigned int binary = 0;
    while (decimal) {
        remainder = decimal % 2;
        decimal /= 2;
        binary += remainder * multiplier;
        multiplier *= 10;
    }
    return binary;
}

unsigned int positive_power(unsigned int base, unsigned int n) {
    /// This function calculates powers for only
    /// positive and relatively smaller values (int).
    if (n < 1) {
        return 1;
    }
    unsigned int result = base;
    while (--n) {
        result *= base;
    }
    return result;
}

unsigned int number_digits_length(int number) {
    /// Returns the number of digits in a given
    /// number. For ex. 476 has 3 digits.
    unsigned int digits = 0;
    while (number) {
        number /= 10;
        ++digits;
    }
    return digits;
}
