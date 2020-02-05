#ifndef UTIL_H
#define UTIL_H_

// We need to include this since it contains
// declaration for struct `timeval`.
#include <sys/time.h>

#define LEDHIGH 10
#define BIT0BREAK 20
#define BIT1BREAK 30
#define CHARBREAK 40
#define TRANSFERBREAK 50

void ms_sleep(int ms);
float timedifference_msec(struct timeval t0, struct timeval t1);
int binary_to_decimal(int binary);
int decimal_to_binary(int decimal);
int positive_power(int base, int n);
int number_digits_length(int number);

#endif
