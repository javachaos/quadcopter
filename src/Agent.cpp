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
	running = stopSig;
	isActivated = false;
}

void Agent::start() {
	running = true;
	if(!isActivated) {
		activate();
		isActivated = true;
	}
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

void Agent::setSignal(sig_atomic_t sig) {
	this->running = sig;
}

Agent::~Agent() {
	name = "";
}

