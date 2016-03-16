/*
 * Communicator.cpp
 *
 *  Created on: Mar 16, 2016
 *      Author: fred
 */

#include "Communicator.h"
#include "Log.h"
#include "Base64.h"
using namespace std;
namespace Quadcopter {

string Communicator::translateForeign(Blackboard::BBMessage msg) {
	Base64 b;
	vector<unsigned char> data;
	vector<unsigned char> m(msg.msg.begin(), msg.msg.end());
	string s = b.base64Encode(m);
	vector<unsigned char> str(s.begin(), s.end());
	data = str;
	data.push_back(static_cast<unsigned char>(msg.from));
	data.push_back(static_cast<unsigned char>(msg.to));

	return string(data.begin(), data.end());
}

Blackboard::BBMessage Communicator::translateLocal(string msg) {
	Base64 b;
	vector<unsigned char> data_local(msg.begin(), msg.end());
	int to = data_local.back();
	data_local.pop_back();
	int from = data_local.back();
	data_local.pop_back();
	data_local = b.base64Decode(msg);
	string smsg = string(data_local.begin(), data_local.end());
	Blackboard::BBMessage message = { smsg, to, from, time(NULL) };
	return message;
}

void Communicator::init(Blackboard* bb) {
	bb->addMessage(ID_LOG,ID_COMM,"Starting Communicator Listener.");
	try {
		io_service.run();
		bb->addMessage(ID_LOG,ID_COMM,"Communicator Listening...");
	} catch (exception& e) {
		clog << kLogNotice << e.what() << endl;
		cerr << e.what() << endl;
	}
}

void Communicator::update(Blackboard* bb) {

}

Communicator::~Communicator() {
}
}
