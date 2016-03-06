/*
 * Agent.h
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#ifndef AGENT_H_
#define AGENT_H_

#include <csignal>
#include <string>
using std::string;

namespace Quadcopter {
class Agent {
public:
	Agent(string name) : name(name), activated(false) {};
	string getName() { return name; }
	void start() {
		if (!isActivated()) {
			activate();
			activated = true;
		}
	}
	virtual void update() = 0;
	bool isActivated() { return activated; }
	virtual ~Agent() = 0;
protected:
	virtual void activate() = 0;
private:
	string name;
	bool activated;
};

inline Agent::~Agent() {}

}
#endif /* AGENT_H_ */
