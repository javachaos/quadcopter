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

	if(m.to == ID_CLIENT) {//Send data to clients and check for responds 2000us timeout.
		//pack(tmp, "%h%h%d%s", m.to, m.from, m.timestamp, m.msg.c_str());
		char* reply = cupdate(m.msg.c_str());
		//if (reply) {
		//	int to, from;
		//	unsigned char msg[COMM_MSG_LENGTH];
		//	double timestamp;
		//	unpack(reply, "%h%h%d%s", to, from, timestamp, msg);
		//	bb->addMessage(to, from,timestamp, string(reinterpret_cast<char*>(msg)));
		//}
                bb->addMessage(ID_LOG, ID_COMM, reply);
	} else {//Check for message from clients
		char* tmp = "Test";
	        char* reply = cupdate(tmp);
		if (reply) {
		    int to, from;
		    char msg[COMM_MSG_LENGTH];
		    //unpack(reply, "%h%h%d%s", to, from, msg);
	            //bb->addMessage(to, from, string(reinterpret_cast<char*>(msg)));
	        }
	}
}

Communicator::~Communicator() {
	cclose();
}

}
