/*
 * Motor.h
 *
 *  Created on: Mar 9, 2016
 *      Author: fred
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_

namespace Quadcopter {
class Motor {
public:
	Motor(int initialSpeed = 0);
	//Create a motor, with initial speed of 0

	bool Calibrate();
	//Calibrate this motor, return true if calibration was a success.

	void setSpeed(int speed);
	//set speed valid range is [0,1000] 0 is full stop

	void increaseSpeed(int stepping);
	//Increase the speed of the motor by stepping amount

	void decreaseSpeed(int stepping);
	//Decressing the speed of the motor by stepping amount

	virtual ~Motor();
	//De-allocate this motor.
private:
	int speed;
};
}
#endif /* SRC_MOTOR_H_ */
