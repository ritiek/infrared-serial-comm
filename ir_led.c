#include <stdio.h>
#include <wiringPi.h>

/* Transfer Specification
    start transmission with the 1st bit that is 1.
    (receiver must assume all previous bits to be 0
    when 8-bit break is received)

    gap to next bit:
    * 100ms => 0
    * 200ms => 1
    * 300ms => 8-bit break
    * 400ms => transfer completed
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
            delay(100);
            break;
        case 1:
            delay(200);
            break;
    }
    emit_signal(pin, 20);
}

int emit_data(int decimal, int pin) {
    int digit;
    int binary = decimal_to_binary(decimal);
    int length = number_digits_length(binary);
    int n_base = positive_power(10, length-1);
    do {
        digit = (binary / n_base) % 10;
        emit_bit(digit, pin);
    }
    while (n_base /= 10);
}

int main() {
    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed !\n");
        return 1;
    }

    int pin = 7;
    pinMode(pin, OUTPUT);
    emit_data('a', pin);

    // Signal a completed transfer session
    delay(400);
    emit_signal(pin, 20);

    return 0;
}
