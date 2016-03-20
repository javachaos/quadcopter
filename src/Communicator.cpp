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

const vector<string> explode(const string& s, const char& c) {
    string buff{""};
    vector<string> v;

    for(auto n:s) {
        if(n != c) {
            buff+=n;
        } else {
            if(n == c && buff != "") {
                v.push_back(buff); buff = "";
            }
        }
    }

    if(buff != "") {
        v.push_back(buff);
    }

    return v;
}

void Communicator::update(Blackboard* bb) {
	Blackboard::BBMessage m = bb->checkForMessage(this->getId());

	if(m.to == ID_COMM) {
	    char const * reply = cupdate(m.toStr().c_str());
            addReply(reply,bb);
        } else {//Querry client for data.
	    char const * tmp = ":::";
	    char const * reply = cupdate(tmp);
            addReply(reply,bb);
        }
}

void Communicator::addReply(char const * reply, Blackboard* bb) {
    if (reply) {
        string s = string(reply);
        vector<string> x{explode(s, ':')};
        int to = std::stoi(x[0]);
        int from = std::stoi(x[1]);
        double timestamp = std::stod(x[2]);
        string msg = x[3];
        if(to == -1 || from == -1 || timestamp == -1) {
           bb->addMessage(ID_LOG, ID_COMM, time(NULL), "COMM_SERVER: msg recv failed bad data.");
        } else {
           bb->addMessage(to, from, timestamp, msg);
        }
    }
}

Communicator::~Communicator() {
	cclose();
}

}
