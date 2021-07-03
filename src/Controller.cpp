/*
 * Controller.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */
#include "Controller.h"

using namespace std;
//using std::clog;
//using std::endl;
//using std::vector;

namespace Quadcopter {

//Controller Ctor
Controller::Controller() :
        Agent("Controller"), bb(make_shared<Blackboard>()), oled(make_shared<OLED>()), disp("Quadcopter v1.0") {
    this->isExit = false;
    auto  comms = make_shared<Communicator>();
    auto motor1 = make_shared<Motor>(ID_MOTOR1, MOTOR_1);
    auto motor2 = make_shared<Motor>(ID_MOTOR2, MOTOR_2);
    auto motor3 = make_shared<Motor>(ID_MOTOR3, MOTOR_3);
    auto motor4 = make_shared<Motor>(ID_MOTOR4, MOTOR_4);

    addDevice(move(  oled));
    addDevice(move(motor1));
    addDevice(move(motor2));
    addDevice(move(motor3));
    addDevice(move(motor4));
    addDevice(move( comms));
}

void Controller::activate() {
        bb->activate();
	clog << kLogNotice << "Controller activated." << endl;
	//Initialize devices
	for (auto it : devices) {
		it->init(bb);
	}
}

void Controller::addDevice(shared_ptr<Device> device) {
	clog << kLogNotice << "Device: " << device->getName()
			<< " added to Controller." << endl;
	devices.push_back(device);
}

shared_ptr<Device> Controller::getDevice(int devId) {
	return devices.at(devId);
}

void Controller::update() {
        auto data = bb->checkForMessage(ID_CONTROLLER);
        auto datum = data.msg;
	if (!datum.empty()) {
	    display(datum);
    }
	for (auto it : devices) {
		if (!this->isExit) {
			it->update(bb);
		} else {
			it->update(bb);
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
//	for(auto it : devices) {
//        delete(it);
//	}
//        delete(bb);
}
}
