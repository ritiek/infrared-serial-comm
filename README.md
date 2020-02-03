# infrared-serial-communication

Transmits data using an IR led to an IR receiver on a Raspberry Pi.
This doesn't use [LIRC](http://www.lirc.org/).

## Installation

Clone this repository:
```console
$ git clone https://github.com/ritiek/infrared-serial-communication
$ cd infrared-serial-communication
```
and run:
```console
$ make
```
If you get an error like this:
```bash
src/transmit.c:3:22: fatal error: wiringPi.h: No such file or directory
 #include <wiringPi.h>
                      ^
compilation terminated.
```

Then it's probably because you don't have WiringPi installed:
```console
$ sudo apt install wiringpi
```
and then run `make` again.

----------

The resultant binaries can be found in `bin/`; `transmit-ir` and `receive-ir`.

## Usage

Let's say you have an IR led connected to GPIO 7 and pointed to an IR receiver
connected to GPIO 4 on the Raspberry Pi. You'll first need to start the receiver
to poll for input on GPIO 4:
```console
$ ./bin/receive-ir 4
```

Now to transmit data through the IR led connected to GPIO 7, in a new terminal run:
```
$ ./bin/transmit-ir 7 "Hello. :D"
```
`transmit-ir` supports reading from `stdin` so you could also do something like this:
```console
$ echo "Hello. :D" | ./bin/transmit-ir 7
```

If everything goes well, you should something like this in both the terminals:
```console
H - 1001000
e - 1100101
l - 1101100
l - 1101100
o - 1101111
. - 101110
  - 100000
: - 111010
D - 1000100
 - 0
Hello. :D
```

## What else could be done?

There are currently no checks implemented for detecting or fixing errors. This would be
nice to have, since I've noticed bits getting switched and similar bad things on the
receiver end when transmitting long strings.

## License

`The MIT License`

See [LICENSE](LICENSE) for more information.
