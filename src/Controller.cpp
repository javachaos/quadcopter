/*
 * Controller.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#include "Controller.h"

#include <unistd.h>
#include <iostream>

#include "Log.h"

using namespace std;

//Controller Ctor
Controller::Controller() :
		Agent("Controller") {
}

void Agent::update() {
	std::clog << kLogNotice << "updating." << std::endl;
	sleep(60);
}

Controller::~Controller() {
	stop();
}

