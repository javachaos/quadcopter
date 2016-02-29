/*
 * Agent.h
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#ifndef AGENT_H_
#define AGENT_H_
#include <string>
using std::string;

using namespace std;

class Agent {
public:
	Agent(string name);
	string getName();
	void start();
	void stop();
	void restart();
	bool isRunning();
protected:
	virtual void activate();
	virtual void update();
	~Agent();
private:
	bool running;
	string name;
};


#endif /* AGENT_H_ */
