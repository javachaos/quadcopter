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
	addMessage(ID_OLED, 1, "Blackboard activated.");
}

bool Blackboard::addMessage(BBMessage msg) {

	if (validateBBM(&msg)) {
            blackboard.insert(map<int, BBMessage>::value_type(msg.to, msg));
            return 1;
	}

	return 0;
}

unsigned long Blackboard::getTimestamp() {
        time_t timer;
        struct tm y2k = {0};
        unsigned long seconds;
        y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
        y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
        time(&timer);  /* get current time; same as: timer = time(NULL)  */
        seconds = (unsigned long) difftime(timer,mktime(&y2k));
        return seconds;
}

bool Blackboard::addMessage(int to, int from, string smsg) {
	unsigned long seconds = getTimestamp();
	BBMessage message = { smsg, to, from, seconds };
	return addMessage(message);
}

bool Blackboard::addMessage(int to, int from, unsigned long timestamp, string smsg) {
	BBMessage message = { smsg, to, from, timestamp };
	return addMessage(message);
}

Blackboard::BBMessage Blackboard::checkForMessage(int id) {
	BBMessage msg;
	std::multimap<int, BBMessage>::iterator iter;
	iter = blackboard.find(id);
	if (iter != blackboard.end()) {
		msg = iter->second;
		blackboard.erase(iter);
	}
	return msg;
}

void Blackboard::purge() {
	std::multimap<int, BBMessage>::iterator iter;
	for (iter = blackboard.begin(); iter != blackboard.end(); ++iter) {
		blackboard.erase(iter);
	}
	clog << kLogNotice << "Blackboard purged." << endl;
}

bool Blackboard::validateBBM(BBMessage *bbmsg) {
	if (bbmsg && bbmsg->timestamp > 0 && !bbmsg->msg.empty()
			&& bbmsg->msg.length() >= 0) {
		return true;
	}
	return false;
}

int Blackboard::size() {
	return blackboard.size();
}

Blackboard::~Blackboard() {
    Blackboard::purge();
}
}

