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
#include "Constants.h"
#include <thread>
#include <chrono>
using std::shared_ptr;

namespace Quadcopter {

Motor::Motor(int devId, string pname, int initialSpeed) :
		Device(devId, pname), speed(initialSpeed), pin_name(pname) {
	get_pwm_key(pin_name.c_str(), key);
}

void Motor::init(shared_ptr<Blackboard> bb) {
	clog << kLogDebug << "Starting motor connected at: " << pin_name << endl;
	pwm_start(key, HIGH_DUTY, FREQUENCY, POLARITY);
	pwm_set_duty_cycle(key, LOW_DUTY);
	clog << kLogDebug << "Calibration complete for " << pin_name << "." << endl;
	std::this_thread::sleep_for (std::chrono::seconds(ONE_SEC));
}

void Motor::setSpeed(float speed) {
	if (speed > MAX_SPEED || speed < MIN_SPEED) {
		return;
	} else {
		pwm_set_duty_cycle(key, remap(speed));
	}
}

void Motor::increaseSpeed(int stepping) {
	if (stepping + speed < MAX_SPEED && stepping + speed >= MIN_SPEED) {
		setSpeed(speed + stepping);
	}
}

void Motor::decreaseSpeed(int stepping) {
	if (speed - stepping < MAX_SPEED && speed - stepping >= MIN_SPEED) {
		setSpeed(speed - stepping);
	}
}

void Motor::update(shared_ptr<Blackboard> bb) {
	Blackboard::BBMessage msg = bb->checkForMessage(getId());
	string str = msg.msg;
	if (!str.empty()) {
		auto speed = strtod(str.c_str(), NULL);
		if (speed > 0 && speed < MAX_SPEED) {
			setSpeed(speed);
		} else {
			//Return a message to the sender, Value Out Of Range (VOOR)
			bb->addMessage(msg.from, getId(), "VOOR");
		}
	}
}

float Motor::remap(double x) {
        auto oldRange = (MAX_SPEED - MIN_SPEED);
        auto newRange = (HIGH_DUTY - LOW_DUTY);
        return (((x - MIN_SPEED) * newRange) / oldRange) + LOW_DUTY;
}

Motor::~Motor() {
	pwm_disable(key);
	pwm_cleanup();
}

}
