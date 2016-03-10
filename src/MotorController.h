/*
 * MotorController.h
 *
 *  Created on: Mar 9, 2016
 *      Author: fred
 */

#ifndef SRC_MOTORCONTROLLER_H_
#define SRC_MOTORCONTROLLER_H_


namespace Quadcopter {

class MotorController {
public:
	MotorController();
	//Motor Ctor.

	bool CalibrateMotors();
	//Calibrate the motors sequentially.

	int setMotorSpeed(int motorId);
	virtual ~MotorController();
private:
	const char* MOTOR1;
	const char* MOTOR2;
	const char* MOTOR3;
	const char* MOTOR4;
};

}
#endif /* SRC_MOTORCONTROLLER_H_ */
