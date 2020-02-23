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

## Running tests

```
$ make test
```

## I'm receiving incorrect characters!

I've found that the current setup works fine for me on my Raspberry Pi 2. However,
it is possible that you are using an older Raspberry Pi with lower specs and may
require more time in decoding the signal. It could also be that other processes
are eating more CPU time.

One thing that might help in such cases would be to try increasing the delay gaps
in [src/util/util.c#L5-L8](https://github.com/ritiek/infrared-serial-communication/blob/852e830d68a40974841226ee126080b4eb5522bd/src/util/util.c#L5-L8).
Such as for example, try changing them to:
```c
const unsigned int BIT0BREAK = 50;
const unsigned int BIT1BREAK = 90;
const unsigned int CHARBREAK = 130;
const unsigned int TRANSFERBREAK = 170;
```
This will make the transfer slower but more reliable.

## What else could be done?

There are currently no checks implemented for detecting or fixing errors. This would be
nice to have, since I've noticed bits getting switched and similar bad things on the
receiver end when transmitting long strings.

Although, I have no idea how we'd achieve something like this since the communication
is unidirectional.

The current transfer rate averages at about 1.5 bytes/sec (when delay gaps in
[src/util/util.c#L5-L8](https://github.com/ritiek/infrared-serial-communication/blob/852e830d68a40974841226ee126080b4eb5522bd/src/util/util.c#L5-L8)
are not modified).

## License

`The MIT License`

See [LICENSE](LICENSE) for more information.
