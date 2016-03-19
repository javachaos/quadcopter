/*
 * Motor.h
 *
 *  Created on: Mar 9, 2016
 *      Author: fred
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_

#include <string>
#include <time.h>
#include "c_drivers/pwm.h"
#include "Log.h"
#include "Constants.h"
#include "Device.h"
using std::clog;
using std::endl;
using std::string;

namespace Quadcopter {

class Motor: public Device {
public:
	Motor(int devId, string pname, int initialSpeed = 0);
	//Create a motor, with initial speed of 0

	void init(Blackboard *bb);
	//Calibrate this motor, return true if calibration was a success.

	void setSpeed(float speed);
	//set speed valid range is [0,1000] 0 is full stop

	void increaseSpeed(int stepping);
	//Increase the speed of the motor by stepping amount

	void decreaseSpeed(int stepping);
	//Decressing the speed of the motor by stepping amount

	void update(Blackboard *bb);

	virtual ~Motor();
	//De-allocate this motor.
private:
	float remap(double x);
	//Remap x from [4,10] to [0,100]
	int speed;
	string pin_name;
	char key[8];
};
}
#endif /* SRC_MOTOR_H_ */
