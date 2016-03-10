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

	bool CalibrateMotors();
	//Calibrate the motors sequentially.

	int setMotorSpeed(int motorId);
//	static const char* MOTOR1 = "P9_16";
//	static const char* MOTOR2 = "P9_42";
//	static const char* MOTOR3 = "P8_13";
//	static const char* MOTOR4 = "P8_19";
	virtual ~MotorController();
private:
};

}
#endif /* SRC_MOTORCONTROLLER_H_ */
