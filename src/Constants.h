/*
 * constants.h
 *
 *  Created on: Feb 29, 2016
 *      Author: alfred
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include <string>
#include "QuadcopterConfig.h"
using std::string;
namespace Quadcopter {

#define DAEMON_NAME "quadcopter"
#define CWD         "/opt/"      + DAEMON_NAME
#define PIDFILE     "/var/run/quadcopter.pid"
#define LOCKFILE    "/var/lock/" + DAEMON_NAME
#define HIGH_DUTY 10.0
#define LOW_DUTY 4.0
#define FREQUENCY 50
#define POLARITY 0
#define MIN_SPEED 1.0
#define MAX_SPEED 1000.0
#define CALIBRATION_SLEEPTIME 500000000L
#define MAX_BLACKBOARD_LENGTH 4096

//Device ID's
enum DEVICE_ID {
	ID_OLED,
	ID_CONTROLLER,
	ID_MOTOR1,
	ID_MOTOR2,
	ID_MOTOR3,
	ID_MOTOR4,
	ID_COMM,
	ID_MEMS,
        ID_GPS,
        ID_PRESSURE,
        ID_TEMPURATURE,
        ID_PUSHBUTTON,
	ID_LOG,
	NUM_DEVICES
};

//Motor ID's
const string MOTOR_1 = "P9_14";
const string MOTOR_2 = "P9_16";
const string MOTOR_3 = "P8_19";
const string MOTOR_4 = "P8_13";

//Communication messages length
const int COMM_MSG_LENGTH = 256;
const unsigned int ONE_SEC = 1;

}
#endif /* CONSTANTS_H_ */

