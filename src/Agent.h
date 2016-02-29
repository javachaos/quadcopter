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

using namespace std;

class Agent {
public:
	Agent(string name);
	string getName();
	void start();
	virtual void update();
protected:
	virtual void activate();
	~Agent();
private:
	string name;
	bool isActivated;
};


#endif /* AGENT_H_ */
