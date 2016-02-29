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
	Agent(string name,volatile sig_atomic_t &stopSig);
	string getName();
	void start();
	bool isRunning();
protected:
	virtual void activate();
	virtual void update();
	~Agent();
private:
	volatile sig_atomic_t done;
	string name;
	bool isActivated;
};


#endif /* AGENT_H_ */
