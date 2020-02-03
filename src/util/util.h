#ifndef UTIL_H
#define UTIL_H_

#include <sys/time.h>

float timedifference_msec(struct timeval t0, struct timeval t1);
int binary_to_decimal(int binary);
int decimal_to_binary(int decimal);
int positive_power(int base, int n);
int number_digits_length(int number);

#endif
