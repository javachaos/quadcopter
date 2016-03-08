#include <unistd.h>
#include <iostream>
#include "Log.h"
#include "Blackboard.h"

using namespace std;
using std::clog;
using std::endl;
using std::multimap;
using std::string;

namespace Quadcopter {

//Ctor
Blackboard::Blackboard(Controller *con) : Agent("Blackboard"), controller(con) {
}

void Blackboard::activate() {
	clog << kLogNotice << "Blackboard activated." << endl;
}

bool Blackboard::addMessage(int callerId, BBMessage msg) {
    clog << kLogNotice << "DeviceID: " << msg.from << " added msg to blackboard." << endl;
    if(controller->getDevice(callerId) != NULL) {
        if(validateBBM(&msg)) {
            blackboard.insert(map<int,BBMessage>::value_type(callerId, msg));
        }
    }
}

bool Blackboard::addMessage(int callerId, int senderId, string smsg) {
  
    BBMessage message = { smsg, callerId, senderId, time(NULL) };
    //message.msg = smsg;
    //message.to = callerId;
    //message.from = controller->getDevice(senderId);
    //message.timestamp = time(NULL);
    return addMessage(callerId, message);
}

bool Blackboard::validateBBM(BBMessage *bbmsg) {
    if(bbmsg
    && bbmsg->timestamp > 0
    && !bbmsg->msg.empty()
    && bbmsg->msg.length() >= 0) {
        Device* dto = controller->getDevice(bbmsg->to);
        Device* dfrom = controller->getDevice(bbmsg->from);
        return dto != NULL && dfrom != NULL;
    }
    return false;
}

void Blackboard::update() {

}

Blackboard::~Blackboard() {

}
}

