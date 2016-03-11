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

    //Device ID's
    enum DEVICE_ID {
		 ID_OLED, ID_CONTROLLER,
		 ID_BLACKBOARD,
		 ID_MOTOR1,
		 ID_MOTOR2,
		 ID_MOTOR3,
		 ID_MOTOR4,
		 TCP_SERVER,
		 NUM_DEVICES
    };

    const int    TCP_SERVER_PORT = 9999;
    const string MOTOR_1 = "P9_14";
    const string MOTOR_2 = "P9_28";
    const string MOTOR_3 = "P8_19";
    const string MOTOR_4 = "P9_42";

}
#endif /* CONSTANTS_H_ */

