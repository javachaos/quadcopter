/*
 * Motor.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: fred
 */
#include <iostream>
#include <stdlib.h>
#include "Motor.h"
#include "Blackboard.h"

namespace Quadcopter {

Motor::Motor(int devId, string pname, int initialSpeed) : Device(devId, pname), speed(initialSpeed), pin_name(pname) {
	get_pwm_key(pin_name.c_str(), key);
}

void Motor::init() {
	clog << kLogDebug << "Starting motor connected at: " << pin_name << endl;
	pwm_start(key, HIGH_DUTY, FREQUENCY, POLARITY);
	struct timespec ts = {0};
	ts.tv_sec  = 0;
	ts.tv_nsec = CALIBRATION_SLEEPTIME;
	nanosleep(&ts, (struct timespec *)NULL);
	pwm_set_duty_cycle(key, LOW_DUTY);
	clog << kLogDebug << "Calibration complete for " << pin_name << "." << endl;
}

void Motor::setSpeed(float speed) {
	if(speed > MAX_SPEED || speed < MIN_SPEED) {
		return;
	} else {
		pwm_set_duty_cycle(key, remap(speed));
	}
}

void Motor::increaseSpeed(int stepping) {
	if(stepping + speed < MAX_SPEED && stepping + speed >= MIN_SPEED) {
		setSpeed(speed + stepping);
	}
}

void Motor::decreaseSpeed(int stepping) {
	if(speed - stepping < MAX_SPEED && speed - stepping >= MIN_SPEED) {
		setSpeed(speed - stepping);
	}
}

void Motor::update(Blackboard *bb) {
	Blackboard::BBMessage msg = bb->checkForMessage(getId());
	if(msg != NULL) {
		string str = msg.msg;
		if (!str.empty()) {
			double speed = strtod(str.c_str(), NULL);
			if(speed > 0 && speed < MAX_SPEED) {
				setSpeed(speed);
			} else {
				//Return a message to the sender, Value Out Of Range (VOOR)
				bb->addMessage(msg.from, getId(), "VOOR");
			}
		} else {
			bb->addMessage(msg.from, getId(), "FAIL");
		}
	}
}

float Motor::remap(float x) {
	return (x-MIN_SPEED)*(HIGH_DUTY-LOW_DUTY)/(MAX_SPEED-MIN_SPEED) + HIGH_DUTY;
}

Motor::~Motor() {
	pwm_disable(key);
	pwm_cleanup();
}

}
