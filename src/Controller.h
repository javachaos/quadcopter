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
#include <memory>

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
	void addDevice(shared_ptr<Device>);
	shared_ptr<Device> getDevice(int devId);
	void setExit(bool);
        void display(string s);
        string getDisplay();
	virtual ~Controller();
protected:
	void init();
	void activate();
private:
	vector<shared_ptr<Device>> devices;
	shared_ptr<Blackboard> bb;
	shared_ptr<OLED> oled;
        string disp;
	bool isExit;
};
}
#endif /* CONTROLLER_H_ */

