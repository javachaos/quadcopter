#include <unistd.h>
#include <iostream>
#include <stddef.h>
#include "Log.h"
#include "Blackboard.h"
#include "Device.h"

using namespace std;
using std::clog;
using std::endl;
using std::multimap;
using std::string;

namespace Quadcopter {

Blackboard::Blackboard() {
}

void Blackboard::activate() {
	clog << kLogNotice << "Blackboard activated." << endl;
	addMessage(ID_OLED, ID_BLACKBOARD, "Blackboard activated.");
}

bool Blackboard::addMessage(int recieverId, BBMessage msg) {
    if(validateBBM(&msg)) {
		clog << kLogDebug << "DeviceID: " << msg.from << " added msg to blackboard." << endl;
		clog << kLogDebug << msg.msg << endl;
        blackboard.insert(map<int,BBMessage>::value_type(recieverId, msg));
        return 1;
    }
    return 0;
}

bool Blackboard::addMessage(int to, int from, string smsg) {
    BBMessage message = { smsg, to, from, time(NULL) };
    return addMessage(to, message);
}

string Blackboard::checkForMessage(int id) {
	BBMessage msg;
	std::multimap<int,BBMessage>::iterator iter;
	iter = blackboard.find(id);
	if(iter != blackboard.end()) {
		blackboard.erase(iter);
		msg = iter->second;
	}
	return msg.msg;
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

