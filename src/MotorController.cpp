/*
 * MotorController.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: fred
 */

#include "MotorController.h"

namespace Quadcopter {

MotorController::MotorController():
		MOTOR1("P9_16"), MOTOR2("P9_42"), MOTOR3("P8_13"), MOTOR4("P8_19") {

}

bool MotorController::CalibrateMotors() {
}

int MotorController::setMotorSpeed(int motorId) {
}

MotorController::~MotorController() {
}
}
