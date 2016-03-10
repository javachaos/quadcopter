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

// Global static pointer used to ensure a single instance of the class.
Blackboard* Blackboard::m_pInstance = NULL;

/** This function is called to create an instance of the class.
    Calling the constructor publicly is not allowed. The constructor
    is private and is only called by this Instance function.
*/

Blackboard* Blackboard::Instance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new Blackboard;

   return m_pInstance;
}

void Blackboard::activate() {
	clog << kLogNotice << "Blackboard activated." << endl;
	addMessage(ID_OLED, ID_BLACKBOARD, "Blackboard activated.");
}

bool Blackboard::addMessage(int recieverId, BBMessage msg) {
    if(m_pInstance->validateBBM(&msg)) {
		clog << kLogDebug << "DeviceID: " << msg.from << " added msg to blackboard." << endl;
        blackboard.insert(map<int,BBMessage>::value_type(recieverId, msg));
        return 1;
    }
    return 0;
}

bool Blackboard::addMessage(int to, int from, string smsg) {
    BBMessage message = { smsg, to, from, time(NULL) };
    return m_pInstance->addMessage(to, message);
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
    delete(m_pInstance);
}
}

