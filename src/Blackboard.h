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
	Blackboard();

	//Define a blackboard message
        struct BBMessage {
	   string msg;
	   int to;
	   int from;
	   time_t timestamp;
           bool operator==(const BBMessage& bb) const {
               return (msg.compare(bb.msg) == 0 && to == bb.to && from == bb.from);
           }
           bool operator!=(const BBMessage& bb) const {
               return !(msg.compare(bb.msg) == 0 || to == bb.to || from == bb.from);
           }
	};

    /**
	 * Add a message to the black board given two id's and a message.
	 */
    bool addMessage(int to, int from, string msg);

    /**
     * Returns the first message for device d and returns it
     * then removes the msg from the Blackboard.
     */
    BBMessage checkForMessage(int id);

    void activate();
    virtual ~Blackboard();
protected:
    bool validateBBM(BBMessage *msg);
    bool addMessage(BBMessage msg);
private:
	multimap<int, BBMessage> blackboard;
};
}
#endif /* BLACKBOARD_H_ */

