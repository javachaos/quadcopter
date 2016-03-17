/*
 * Communicator.cpp
 *
 *  Created on: Mar 16, 2016
 *      Author: fred
 */

#include "Communicator.h"
using namespace std;
namespace Quadcopter {

void Communicator::init(Blackboard* bb) {
	bb->addMessage(ID_LOG,ID_COMM,"Initializing Communicator Listener.");
	cinit();
	bb->addMessage(ID_LOG,ID_COMM,"Communicator Initialized.");
}

void Communicator::update(Blackboard* bb) {
	//TODO complete this Communicator::update() method.
	Blackboard::BBMessage m = bb->checkForMessage(this->getId());
	int MSG_LENGTH = 256;
	if(m.to > 0) {//Send data to clients and check for responds 2000us timeout.
		unsigned char tmp[MSG_LENGTH];
		pack(tmp, "%h%h%d%s", m.to, m.from, m.timestamp, m.msg.c_str());
		unsigned char* reply = cupdate(tmp);
		if (reply) {
			int to, from;
			unsigned char msg[MSG_LENGTH];
			double timestamp;
			unpack(reply, "%h%h%d%s", to, from, timestamp, msg);
			bb->addMessage(to, from,timestamp, string(reinterpret_cast<char*>(msg)));
		}
	} else {//Check for message from clients
		const unsigned char* tmp = 0;
	    unsigned char* reply = cupdate(tmp);
		if (reply) {
		    int to, from;
		    unsigned char msg[MSG_LENGTH];
		    unpack(reply, "%h%h%d%s", to, from, msg);
	        bb->addMessage(to, from, string(reinterpret_cast<char*>(msg)));
	    }
	}
}

Communicator::~Communicator() {
	cclose();
}

}
