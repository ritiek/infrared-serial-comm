#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "test_util.h"

void test_timedifference_msec() {
    struct timeval past;
    struct timeval now;
    gettimeofday(&past, 0);
    usleep(150000);
    gettimeofday(&now, 0);
    float difference = timedifference_msec(past, now);
    assert(difference > 150);
    assert(difference < 151);
}

void test_binary_to_decimal() {
    assert(binary_to_decimal(10) == 2);
    assert(binary_to_decimal(101) == 5);
    assert(binary_to_decimal(10010) == 18);
    assert(binary_to_decimal(1100101) == 'e');
}

void test_decimal_to_binary() {
    assert(decimal_to_binary(2) == 10);
    assert(decimal_to_binary(5) == 101);
    assert(decimal_to_binary(18) == 10010);
    assert(decimal_to_binary('e') == 1100101);
}

void test_positive_power() {
    assert(positive_power(2, 3) == 8);
    assert(positive_power(3, 4) == 81);
    assert(positive_power(2, 10) == 1024);
    assert(positive_power(5, 3) == 125);
}

void test_number_digits_length() {
    assert(number_digits_length(2341) == 4);
    assert(number_digits_length(12) == 2);
    assert(number_digits_length(476) == 3);
    assert(number_digits_length(53457) == 5);
}
