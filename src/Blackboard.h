#ifndef BLACKBOARD_H_
#define BLACKBOARD_H_
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <time.h>
#include "Constants.h"
#include "Agent.h"


using std::string;
using std::multimap;
using std::ostringstream;
namespace Quadcopter {

class Blackboard {
public:
	Blackboard();

	//Define a blackboard message
	struct BBMessage {
		string msg;
		int to;
		int from;
		double timestamp;
                string toStr() {
                    ostringstream os;
                    os << to << ":" << from << ":" << timestamp << ":" << msg;
                    return os.str();
                }
	};

	/**
	 * Add a message to the black board given two id's and a message.
	 */
	bool addMessage(int to, int from, string msg);

	bool addMessage(int to, int from, double timestamp, string smsg);

	/**
	 * Returns the first message for device d and returns it
	 * then removes the msg from the Blackboard.
	 */
	BBMessage checkForMessage(int id);

	void activate();

	/**
	 * Remove all blackboard entries
	 */
	void purge();

	/**
	 * Return the length of this multi map
	 */
	int size();

	virtual ~Blackboard();
protected:
	bool validateBBM(BBMessage *msg);
	bool addMessage(BBMessage msg);
private:
	multimap<int, BBMessage> blackboard;
};
}
#endif /* BLACKBOARD_H_ */

