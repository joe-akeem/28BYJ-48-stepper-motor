#include "28BYJ48StepperMotor.hpp"
#include <iostream>
#include <ctime>

using namespace std;

const bool 28BYJ48StepperMotor::WAVE_DRIVE_MOTOR_SEQUENCE[][4] = {
		{ LOW,  LOW,  LOW,  HIGH },
		{ LOW,  LOW,  HIGH, LOW },
		{ LOW,  HIGH, LOW,  LOW },
		{ HIGH, LOW,  LOW,  LOW },
		{ LOW,  LOW,  LOW,  HIGH },
		{ LOW,  LOW,  HIGH, LOW },
		{ LOW,  HIGH, LOW,  LOW },
		{ HIGH, LOW,  LOW,  LOW }
};

const bool 28BYJ48StepperMotor::FULL_STEP_MOTOR_SEQUENCE[][4] = {
		{ LOW,  LOW,  LOW,  HIGH },
		{ LOW,  LOW,  HIGH, LOW },
		{ LOW,  HIGH, LOW,  LOW },
		{ HIGH, LOW,  LOW,  LOW },
		{ LOW,  LOW,  LOW,  HIGH },
		{ LOW,  LOW,  HIGH, LOW },
		{ LOW,  HIGH, LOW,  LOW },
		{ HIGH, LOW,  LOW,  LOW }
};

const bool 28BYJ48StepperMotor::HALF_STEP_MOTOR_SEQUENCE[][4] = {
		{ LOW,  LOW,  LOW,  HIGH },
		{ LOW,  LOW,  HIGH, HIGH },
		{ LOW,  LOW,  HIGH, LOW },
		{ LOW,  HIGH, HIGH, LOW },
		{ LOW,  HIGH, LOW,  LOW },
		{ HIGH, HIGH, LOW,  LOW },
		{ HIGH, LOW,  LOW,  LOW },
		{ HIGH, LOW,  LOW,  HIGH }
};

28BYJ48StepperMotor::28BYJ48StepperMotor(const unsigned int pinA, const unsigned int pinB, const unsigned int pinC,
		const unsigned int pinD, const unsigned int stepDuration, const SteppingMethod steppingMethod)
{
	inputPins[0] = pinA;
	inputPins[1] = pinB;
	inputPins[2] = pinC;
	inputPins[3] = pinD;

	for (int i = 0; i < 4; i++) {
		pinMode(inputPins[i], OUTPUT);
	}

	this->stepDuration = stepDuration;
	this->steppingMethod = steppingMethod;
}

void 28BYJ48StepperMotor::fullRotation(const int noOfRotations) {
	halfRotation(2*noOfRotations);
}

void 28BYJ48StepperMotor::halfRotation(const int noOfHalfRotations) {
	quarterRotation(2*noOfHalfRotations);
}

void 28BYJ48StepperMotor::quarterRotation(const int noOfQuarterRotations) {
	switch (steppingMethod) {
		case HALF_STEP:
			step(2 * 512 * noOfQuarterRotations);
			break;
		default:
			step(512 * noOfQuarterRotations);
			break;
	}
}

void 28BYJ48StepperMotor::angleRotation(const float angle) {
	int steps;
	switch (steppingMethod) {
		case HALF_STEP:
			steps = (int)(512*8*angle)/360;
			break;
		default:
			steps = (int)(512*4*angle)/360;
			break;
	}
	step(steps);
}

void 28BYJ48StepperMotor::setStepDurartion(const unsigned int stepDuration) {
	this->stepDuration = stepDuration;
}

void 28BYJ48StepperMotor::setSteppingMethod(const SteppingMethod steppingMethod) {
	this->steppingMethod = steppingMethod;
}

void 28BYJ48StepperMotor::step(const int noOfSteps) {
	if (noOfSteps > 0) {
		for (int currentStep = noOfSteps; currentStep > 0; currentStep--) {
			int currentSequenceNo = currentStep % 8;
			writeSequence(currentSequenceNo);
		}
	} else {
		for (int currentStep = 0; currentStep < abs(noOfSteps); currentStep++) {
			int currentSequenceNo = currentStep % 8;
			writeSequence(currentSequenceNo);
		}
	}
}

void 28BYJ48StepperMotor::writeSequence(const unsigned int sequenceNo) {
	for (int i = 0; i < 4; i++) {
		switch(steppingMethod) {
			case WAVE_DRIVE:
				digitalWrite(inputPins[i], WAVE_DRIVE_MOTOR_SEQUENCE[sequenceNo][i]);
				break;
			case FULL_STEP:
				digitalWrite(inputPins[i], FULL_STEP_MOTOR_SEQUENCE[sequenceNo][i]);
				break;
			default:
				digitalWrite(inputPins[i], HALF_STEP_MOTOR_SEQUENCE[sequenceNo][i]);
				break;
		}
	}
	delay(stepDuration);
	for (int i = 0; i < 4; i++) {
		digitalWrite(inputPins[i], LOW);
	}
}

void 28BYJ48StepperMotor::performDemo() {
	clock_t begin, end;

	cout << "Full rotation clockwise in wave drive method with stepDuration=3ms... " << endl;
	begin = clock();
	setSteppingMethod(WAVE_DRIVE);
	setStepDurartion(3);
	fullRotation(1);
	end = clock();
	cout << "(took " << (end - begin) << ")" << endl;

	cout << "Full rotation counterclockwise in full step method with stepDuration=3ms... " << endl;
	begin = clock();
	setSteppingMethod(FULL_STEP);
	setStepDurartion(3);
	fullRotation(-1);
	end = clock();
	cout << "(took " << (end - begin) << ")" << endl;

	cout << "Full rotation clockwise in half step method with stepDuration=3ms... " << endl;
	begin = clock();
	setSteppingMethod(HALF_STEP);
	setStepDurartion(3);
	fullRotation(1);
	end = clock();
	cout << "(took " << (end - begin) << ")" << endl;

	cout << "Half rotation counterclockwise in full step method with stepDuration=3ms... " << endl;
	begin = clock();
	setSteppingMethod(FULL_STEP);
	setStepDurartion(3);
	halfRotation(-1);
	end = clock();
	cout << "(took " << (end - begin) << ")" << endl;

	cout << "Quarter rotation clockwise in full step method with stepDuration=3ms... " << endl;
	begin = clock();
	setSteppingMethod(FULL_STEP);
	setStepDurartion(3);
	quarterRotation(1);
	end = clock();
	cout << "(took " << (end - begin) << ")" << endl;

	cout << "180 degree rotation counterclockwise in full step method with stepDuration=3ms... " << endl;
	begin = clock();
	setSteppingMethod(FULL_STEP);
	setStepDurartion(3);
	angleRotation(-180);
	end = clock();
	cout << "(took " << (end - begin) << ")" << endl;

	cout << "90 degree rotation clockwise in half step method with stepDuration=3ms... " << endl;
	begin = clock();
	setSteppingMethod(HALF_STEP);
	setStepDurartion(3);
	angleRotation(270);
	end = clock();
	cout << "(took " << (end - begin) << ")" << endl;
}

