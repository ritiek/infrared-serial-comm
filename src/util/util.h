#pragma once

// We need to include this since it contains
// declaration for struct `timeval`.
#include <sys/time.h>

extern const unsigned int LEDHIGH;
extern const unsigned int BIT0BREAK;
extern const unsigned int BIT1BREAK;
extern const unsigned int CHARBREAK;
extern const unsigned int TRANSFERBREAK;

void ms_sleep(unsigned int ms);
float timedifference_msec(struct timeval t0, struct timeval t1);
unsigned int binary_to_decimal(unsigned int binary);
unsigned int decimal_to_binary(unsigned int decimal);
unsigned int positive_power(unsigned int base, unsigned int n);
unsigned int number_digits_length(int number);
