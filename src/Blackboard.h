#ifndef BLACKBOARD_H_
#define BLACKBOARD_H_
#include <string.h>
#include <map>
#include <utility>
#include <time.h>
#include "Constants.h"
#include "Agent.h"

using std::string;
using std::multimap;

namespace Quadcopter {

class Blackboard {
public:
	static Blackboard* Instance();

	//Define a blackboard message
	typedef struct {
	   string msg;
	   int to;
	   int from;
	   time_t timestamp;
	} BBMessage;

	/**
	 * Add a message to the blackboard given device id and msg.
	 */
	bool addMessage(int recieverId, BBMessage msg);

	/**
	 * Add a message to the black board given two id's and a message.
	 */
    bool addMessage(int to, int from, string msg);

    /**
     * Returns the first message for device d and returns it
     * then removes the msg from the Blackboard.
     */
    string checkForMessage(int id);

	void activate();
	virtual ~Blackboard();
private:
    bool validateBBM(BBMessage *msg);
	multimap<int, BBMessage> blackboard;
	Blackboard(){};
	Blackboard(Blackboard const&){};
	Blackboard& operator=(Blackboard const&){};
	static Blackboard* m_pInstance;
};
}
#endif /* BLACKBOARD_H_ */

