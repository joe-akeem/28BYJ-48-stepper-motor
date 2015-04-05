#ifndef STEPPER_MOTOR_HPP
#define STEPPER_MOTOR_HPP

#include <wiringPi.h>

/**
 * Represents the 28BYJ-48 stepper motor, and the ULN2003 driver board
 * connected to a Raspberry Pi. It uses wiringPi to set the I/O pins on
 * the Raspberry Pi.
 * This class supports the stepping methods 'wave drive', 'full step' and
 * 'half step' (see <https://www.youtube.com/watch?v=B86nqDRskVU> for details.)
 *
 * @see <http://wiringpi.com/>
 */
class 28BYJ48StepperMotor {
public:

	/**
	 * The stepping method to be used by the motor.
	 * @see <https://www.youtube.com/watch?v=B86nqDRskVU>
	 */
	enum SteppingMethod {WAVE_DRIVE, FULL_STEP, HALF_STEP};

	/**
	 * Connects a new stepper motor instance with the pins on a Raspberry Pi
	 * and sets a step duration and a stepping method.
	 * <em>This method uses the wiringPi numbering system of the Raspberry Pi.</em>
	 *
	 * @param pinA - the Raspberry Pi pin the pin A of the stepper motor is connected to
	 * @param pinB - the Raspberry Pi pin the pin B of the stepper motor is connected to
	 * @param pinC - the Raspberry Pi pin the pin C of the stepper motor is connected to
	 * @param pinD - the Raspberry Pi pin the pin D of the stepper motor is connected to
	 * @param stepDuration - the pause between two steps in milliseconds.
	 * @param steppingmethod - the stepping method to be used by the motor
	 *
	 */
	28BYJ48StepperMotor(const unsigned int pinA, const unsigned int pinB, const unsigned int pinC,
			const unsigned int pinD, const unsigned int stepDuration, const SteppingMethod steppingMethod = HALF_STEP);

	/**
	 * Sets the duration of the pause between each step in milliseconds.
	 *
	 * @param stepDuration - the pause in milliseconds between each step
	 */
	void setStepDurartion(const unsigned int stepDuration);

	/**
	 * Sets the stepping method of the stepper motor.
	 *
	 * @param steppingMethod - the stepping method to set.
	 */
	void setSteppingMethod(const SteppingMethod steppingMethod);

	/**
	 * Causes the motor to perform full rotations. If the passed value
	 * is positive the motor will rotate clockwise, if negative it will
	 * rotate counterclockwise.
	 *
	 * @param noOfRotations - the amount of full rotations to perform
	 */
	void fullRotation(const int noOfRotations);

	/**
	 * Causes the motor to perform half rotations. If the passed value
	 * is positive the motor will rotate clockwise, if negative it will
	 * rotate counterclockwise.
	 *
	 * @param noOfRotations - the amount of half rotations to perform
	 */
	void halfRotation(const int noOfHalfRotations);

	/**
	 * Causes the motor to perform quarter rotations. If the passed value
	 * is positive the motor will rotate clockwise, if negative it will
	 * rotate counterclockwise.
	 *
	 * @param noOfRotations - the amount of quarter rotations to perform
	 */
	void quarterRotation(const int noOfQuarterRotations);

	/**
	 * Rotates the motor by a specified angle. Note that the step angle
	 * of the motor is 0.19 degrees in full step and wave drive methods
	 * and 0.09 degrees in half step method.
	 *
	 * @param angle - the angle in degrees
	 */
	void angleRotation(const float angle);

	/**
	 * Moves the stepper motor by one step. Depending on the stepping method
	 * this will move the motor by 0.19 degrees in case of full step and wave drive methods
	 * or 0.09 degrees in half step method. If the passed value is positive the motor
	 * will rotate clockwise, if negative it will rotate counterclockwise.
	 */
	void step(const int noOfSteps);

	/**
	 * Performs a demo of the various methods to move the motor.
	 */
	void performDemo();

private:
	/** The motor sequence for the wave drive stepping method. **/
	static const bool WAVE_DRIVE_MOTOR_SEQUENCE[][4];

	/** The motor sequence for the full step stepping method. **/
	static const bool FULL_STEP_MOTOR_SEQUENCE[][4];

	/** The motor sequence for the half step stepping method. **/
	static const bool HALF_STEP_MOTOR_SEQUENCE[][4];

	/** The current step duration in milliseconds. **/
	int stepDuration;

	/** Holds the Raspberry Pi pin numbers for pins A though D of the stepper motor. **/
	int inputPins[4];

	/** The current stepping method of this motor **/
	SteppingMethod steppingMethod;

	/**
	 * Writes the motor sequence to the Raspberry Pi pins.
	 *
	 * @param sequenceNo - references a sequence in one of the motor sequences above.
	 */
	void writeSequence(const unsigned int sequenceNo);
};

#endif
