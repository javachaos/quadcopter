#ifndef BLACKBOARD_H_
#define BLACKBOARD_H_
#include <string.h>
#include "Controller.h"
#include "Device.h"
#include "Agent.h"
#include <map>
#include <utility>
#include <time.h>

using std::string;
using std::multimap;

namespace Quadcopter {

class Blackboard : public Agent {
public:
    Blackboard(Controller *con);
	struct BBMessage {
          string msg;
          int to;
          int from;
          time_t timestamp;
        };
        void update();
	bool addMessage(int deviceId,BBMessage msg);
        bool addMessage(int, int, string);
	virtual ~Blackboard();
protected:
	void init();
	void activate();
private:
        bool validateBBM(BBMessage *msg);       
	multimap<int,BBMessage> blackboard;
        Controller *controller;
};
}
#endif /* BLACKBOARD_H_ */

