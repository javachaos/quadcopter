/*
 * Controller.h
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <string.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "Device.h"
#include "Agent.h"
#include "Motor.h"
#include "OLED.h"
#include "Communicator.h"
#include "QuadcopterConfig.h"

using std::string;
using std::vector;

namespace Quadcopter {
class Controller: public Agent {
public:
	Controller();
	void update();
	void addDevice(Device*);
	Device* getDevice(int devId);
	void setExit(bool);
        void display(string s);
        string getDisplay();
	virtual ~Controller();
protected:
	void init();
	void activate();
private:
	vector<Device*> devices;
	Blackboard *bb;
        OLED *oled;
        string disp;
	bool isExit;
};
}
#endif /* CONTROLLER_H_ */

