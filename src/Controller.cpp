/*
 * Controller.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */
#include "Controller.h"

using namespace std;
using std::clog;
using std::endl;
using std::vector;

namespace Quadcopter {

//Controller Ctor
Controller::Controller() :
        Agent("Controller"), bb(new Blackboard), oled(new OLED), disp("Quadcopter v1.0") {
    this->isExit = false;
    addDevice(oled);
    Communicator *comms = new Communicator;
    Motor *m1 = new Motor(ID_MOTOR1, MOTOR_1);
    Motor *m2 = new Motor(ID_MOTOR2, MOTOR_2);
    Motor *m3 = new Motor(ID_MOTOR3, MOTOR_3);
    Motor *m4 = new Motor(ID_MOTOR4, MOTOR_4);
    addDevice(m1);
    addDevice(m2);
    addDevice(m3);
    addDevice(m4);
    addDevice(comms);
}

void Controller::activate() {
        bb->activate();
	clog << kLogNotice << "Controller activated." << endl;
	//Initialize devices
	for (vector<Device*>::iterator it = devices.begin(); it != devices.end();
			++it) {
		(*it)->init(bb);
	}
}

void Controller::addDevice(Device *device) {
	clog << kLogNotice << "Device: " << device->getName()
			<< " added to Controller." << endl;
	devices.push_back(device);
}

Device* Controller::getDevice(int devId) {
	return devices.at(devId);
}

void Controller::update() {
        Blackboard::BBMessage data = bb->checkForMessage(ID_CONTROLLER);
        string datum = data.msg;
	if (!datum.empty()) {
	    display(datum);
        }
	for (vector<Device*>::iterator it = devices.begin(); it != devices.end();
			++it) {
		if (!this->isExit) {
			(*it)->update(bb);
		} else {
			(*it)->update(bb);
			break;
		}
	}

	//Purge the blackboard if it gets too large.
	if (bb->size() > MAX_BLACKBOARD_LENGTH) {
		bb->purge();
	}
}

void Controller::setExit(bool exit) {
	this->isExit = exit;
}

void Controller::display(string s) {
    oled->write(s);
}

string Controller::getDisplay() {
    return disp;
}

Controller::~Controller() {
	for (vector<Device*>::iterator it = devices.begin(); it != devices.end();
			++it) {
                delete(*it);
	}
        delete(bb);
}
}
