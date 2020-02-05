#pragma once

// We need to include this since it contains
// declaration for struct `timeval`.
#include <sys/time.h>

extern const int LEDHIGH;
extern const int BIT0BREAK;
extern const int BIT1BREAK;
extern const int CHARBREAK;
extern const int TRANSFERBREAK;

void ms_sleep(int ms);
float timedifference_msec(struct timeval t0, struct timeval t1);
int binary_to_decimal(int binary);
int decimal_to_binary(int decimal);
int positive_power(int base, int n);
int number_digits_length(int number);
