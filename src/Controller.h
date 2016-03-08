/*
 * Controller.h
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <string.h>
#include "Device.h"
#include "Agent.h"
#include <vector>
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
	virtual ~Controller();
protected:
	void init();
	void activate();
private:
	vector<Device*> devices;
        bool isExit;
};
}
#endif /* CONTROLLER_H_ */

