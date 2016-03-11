#include <unistd.h>
#include <iostream>
#include <stddef.h>
#include <time.h>
#include "Log.h"
#include "Blackboard.h"
#include "Device.h"
#include "QuadcopterConfig.h"
using namespace std;
using std::clog;
using std::endl;
using std::multimap;
using std::string;

namespace Quadcopter {

Blackboard::Blackboard() {
}

void Blackboard::activate() {
	addMessage(ID_OLED, ID_BLACKBOARD, "Blackboard activated.");
}

bool Blackboard::addMessage(BBMessage msg) {
    if(validateBBM(&msg)) {
#ifdef DEBUG
        struct tm * timeinfo;
        time_t temp = msg.timestamp;
        time(&temp);
        timeinfo = localtime(&temp);
		clog << kLogDebug << "DeviceID: " << msg.from << " added msg to blackboard. At: " << asctime(timeinfo) << endl;
#endif //DEBUG
		clog << kLogDebug << msg.msg << endl;
        blackboard.insert(map<int,BBMessage>::value_type(msg.to, msg));
        return 1;
    }
    return 0;
}

bool Blackboard::addMessage(int to, int from, string smsg) {
    BBMessage message = { smsg, to, from, time(NULL) };
    return addMessage(message);
}

Blackboard::BBMessage Blackboard::checkForMessage(int id) {
	BBMessage msg = {0};
	std::multimap<int,BBMessage>::iterator iter;
	iter = blackboard.find(id);
	if(iter != blackboard.end()) {
		blackboard.erase(iter);
		msg = iter->second;
	}
	return msg;
}

bool Blackboard::validateBBM(BBMessage *bbmsg) {
    if(bbmsg
    && bbmsg->timestamp > 0
    && !bbmsg->msg.empty()
    && bbmsg->msg.length() >= 0) {
        return true;
    }
    return false;
}

Blackboard::~Blackboard() {
}
}

