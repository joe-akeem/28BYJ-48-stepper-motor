# API for 28BYJ-48 Stepper Motor and ULN2003 Driver on Rasperry Pi

A handy API for the 28BYJ-48 stepper motor connected to the ULN2003 driver board and a Raspberry Pi.

## Building and installing

`$ make`

will create libStepperMotor28BYJ48.so in the local directory.

`$ sudo make install`

will install it to /usr/local/lib

## Usage

Before using the API wiringPi must be set up as follows:

```
#include <wiringPi.h>
...
if (wiringPiSetup() == -1) {
	cerr << "'Failed to setup wiringPi" << endl;
	exit (EXIT_FAILURE);
}
```

Then operating the motor is straight forward. E.g. if it is
connected to the Raspberry Pi using (wiringPi) pins number 1, 4, 5 and 6
and a step duration of 3 milliseconds the just call the following to
let the motor perform a little demo.

```
StepperMotor motor(1, 4, 5, 6, 3);
motor.performDemo();
```

The documentation in StepperMotor28BYJ48.hpp should be self explaining.