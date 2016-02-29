/*
 * Agent.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#include "Agent.h"
using std::string;
using namespace std;

//Agent ctor given name
Agent::Agent(string name, volatile sig_atomic_t &stopSig) {
	this->name = name;
	done = stopSig;
	isActivated = false;
}

void Agent::start() {
	if(!isActivated) {
		activate();
		isActivated = true;
	}
}

bool Agent::isRunning() {
	return this->done;
}

string Agent::getName() {
	return name;
}

void Agent::activate() {
	while(!done) {
		update();
	}
}

Agent::~Agent() {
	name = "";
}

