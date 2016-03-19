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

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
   std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

template <typename T>
T lexical_cast(const std::string& s)
{
    std::stringstream ss(s);

    T result;
    if ((ss >> result).fail() || !(ss >> std::ws).eof())
    {
        return -1;
    }

    return result;
}

void Communicator::update(Blackboard* bb) {
	Blackboard::BBMessage m = bb->checkForMessage(this->getId());

	if(m.to == ID_COMM) {
	    char* reply = cupdate(m.toStr().c_str());
            addReply(reply,bb);
        } else {//Querry client for data.
	    char* tmp = ":::";
	    char* reply = cupdate(tmp);
            addReply(reply,bb);
        }
}

void Communicator::addReply(char* reply, Blackboard* bb) {
    if (reply) {
        string s = string(reply);
        vector<string> x = split(s, ':');
        int to = lexical_cast<int>(x[0]);
        int from = lexical_cast<int>(x[1]);
        double timestamp = lexical_cast<double>(x[2]);
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
