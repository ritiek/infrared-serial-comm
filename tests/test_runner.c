#include <stdio.h>
#include "util/test_util.h"

void test_util(char run_msg[], char ok_msg[]) {
    printf(run_msg, "util/util.c:test_timedifference_msec");
    test_timedifference_msec();
    printf(ok_msg);

    printf(run_msg, "util/util.c:test_binary_to_decimal");
    test_binary_to_decimal();
    printf(ok_msg);

    printf(run_msg, "util/util.c:test_decimal_to_binary");
    test_decimal_to_binary();
    printf(ok_msg);

    printf(run_msg, "util/util.c:test_positive_power");
    test_positive_power();
    printf(ok_msg);

    printf(run_msg, "util/util.c:test_number_digits_length");
    test_number_digits_length();
    printf(ok_msg);
}

int main() {
    char run_msg[100] = "Executing %s\n";
    char ok_msg[4] = "OK\n";

    test_util(run_msg, ok_msg);

    return 0;
}
