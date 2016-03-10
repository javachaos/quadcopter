/*
 * Controller.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sstream>

#include "Controller.h"
#include "QuadcopterConfig.h"
#include "Log.h"

using namespace std;
using std::clog;
using std::endl;
using std::vector;

namespace Quadcopter {

//Controller Ctor
Controller::Controller(Blackboard *inst) : Agent("Controller"), bb(inst){
    this->isExit = false;
}

void Controller::activate() {
	clog << kLogNotice << "Controller activated." << endl;

	//Initialize devices
	for (vector<Device*>::iterator it = devices.begin(); it != devices.end();
			++it) {
		(*it)->init();
	}
}

void Controller::addDevice(Device *device) {
	clog << kLogNotice << "Device: " << device->getName() << " added to Controller." << endl;
	devices.push_back(device);
}

Device* Controller::getDevice(int devId) {
        return devices.at(devId);
}

void Controller::update() {
	for (vector<Device*>::iterator it = devices.begin(); it != devices.end();
			++it) {
                if (!this->isExit) {
                    (*it)->update(bb);
                } else {
                    (*it)->update(bb);
                }
	}
}

void Controller::setExit(bool exit) {
    this->isExit = exit;
}

Controller::~Controller() {
    for (vector<Device*>::iterator it = devices.begin(); it != devices.end(); ++it) {
        (*it)->~Device();
    }
}

}
