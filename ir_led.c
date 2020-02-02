#include <stdio.h>
#include <wiringPi.h>

/* Transfer Specification
    start transmission with the 1st bit that is 1.

    gap to next bit:
    * 80ms => 0
    * 120ms => 1
    * 160ms => character break
    * 200ms => transfer completed

    The LED must be HIGH for 30ms for each signal
*/

int number_digits_length(int number) {
    int digits = 0;
    while (number) {
        number /= 10;
        ++digits;
    }
    return digits;
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

int emit_signal(int pin, int duration) {
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
}

int positive_power(int base, int n) {
    if (n < 0) {
        return 1;
    }
    int result = base;
    while (--n) {
        result *= base;
    }
    return result;
}

int emit_bit(int bit, int pin) {
    switch (bit) {
        case 0:
            delay(80);
            break;
        case 1:
            delay(120);
            break;
    }
    emit_signal(pin, 30);
}

int emit_character(int decimal, int pin) {
    int digit;
    int binary = decimal_to_binary(decimal);
    printf("%c - %d\n", decimal, binary);
    int length = number_digits_length(binary);
    int n_base = positive_power(10, length-1);
    do {
        digit = (binary / n_base) % 10;
        emit_bit(digit, pin);
    }
    while (n_base /= 10);
}

int emit_string(char string[], int pin) {
    int i = 0;
    while (string[i]) {
        emit_character(string[i++], pin);
        delay(160);
        emit_signal(pin, 20);
    }
}

int main() {
    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed !\n");
        return 1;
    }

    int pin = 7;
    pinMode(pin, OUTPUT);

    char string[1000] = "They call me IR.";
    emit_string(string, pin);

    // Signal a completed transfer session
    delay(200);
    emit_signal(pin, 20);
    printf("%s\n", string);

    return 0;
}
