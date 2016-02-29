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
Agent::Agent(string name){
	this->name = name;
	isActivated = false;
}

void Agent::start() {
	if(!isActivated) {
		activate();
		isActivated = true;
	}
}

string Agent::getName() {
	return name;
}

Agent::~Agent() {
	name = "";
}

