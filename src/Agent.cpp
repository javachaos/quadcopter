/*
 * Agent.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */
#include "Agent.h"
#include <string>
using std::string;
using namespace std;

//Agent ctor given name
Agent::Agent(string name) {
	this->name = name;
	running = false;
}


void Agent::start() {
	running = true;
	activate();
}

void Agent::stop() {
	running = false;
}

void Agent::restart() {
	Agent::stop();
	Agent::start();
}
bool Agent::isRunning() {
	return this->running;
}

string Agent::getName() {
	return name;
}

void Agent::activate() {
	while(running) {
		update();
	}
}

Agent::~Agent() {
	name = "";
}

