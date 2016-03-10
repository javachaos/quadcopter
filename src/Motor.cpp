/*
 * Motor.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: fred
 */

#include "Motor.h"
#include "Blackboard.h"
namespace Quadcopter {

Motor::Motor(string pname, int initialSpeed) : Device(ID_MOTOR,pname), speed(initialSpeed), pin_name(pname) {

}

void Motor::init() {
	Blackboard::Instance()->addMessage(ID_OLED, getId(), "Starting motor connected at: " + pin_name);
	pwm_start(pin_name.c_str(), HIGH_DUTY, FREQUENCY, POLARITY);
	struct timespec ts = {0};
	ts.tv_sec  = 0;
	ts.tv_nsec = CALIBRATION_SLEEPTIME;
	nanosleep(&ts, (struct timespec *)NULL);
	pwm_set_duty_cycle(pin_name.c_str(), LOW_DUTY);
	Blackboard::Instance()->addMessage(ID_OLED, getId(), "Done.");
}

void Motor::setSpeed(int speed) {
	if(speed > MAX_SPEED || speed < MIN_SPEED) {
		clog << kLogNotice << "Motor speed out of range: " << speed << endl;
		return;
	} else {
		pwm_set_duty_cycle(pin_name.c_str(), remap(speed));
	}
}

void Motor::increaseSpeed(int stepping) {
	if(stepping + speed < MAX_SPEED && stepping + speed >= MIN_SPEED) {
		setSpeed(speed + stepping);
	} else {
		clog << kLogNotice << "Attempting to increase speed out of range: " << stepping + speed << endl;
	}
}

void Motor::decreaseSpeed(int stepping) {
	if(speed - stepping < MAX_SPEED && speed - stepping >= MIN_SPEED) {
		setSpeed(speed - stepping);
	} else {
		clog << kLogNotice << "Attempting to decrease speed out of range: " << speed - stepping << endl;
	}
}

void Motor::update(Blackboard *bb) {
//TODO Complete
}

float Motor::remap(float x) {
	return (x-MIN_SPEED)*(HIGH_DUTY-LOW_DUTY)/(MAX_SPEED-MIN_SPEED) + HIGH_DUTY;
}

Motor::~Motor() {
	pwm_disable(pin_name.c_str());
	pwm_cleanup();
}

}
