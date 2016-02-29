/*
 * Controller.h
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */
#include <string.h>
#include <map>
#include "Device.h"
#include "Agent.h"
using namespace std;

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller: public Agent {
public:
	Controller();
protected:
	void init();
	~Controller();
private:
	//std::map<string, Device> devices;
};

#endif /* CONTROLLER_H_ */

