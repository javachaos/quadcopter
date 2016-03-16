/*
 * Communicator.h
 *
 *  Created on: Mar 16, 2016
 *      Author: fred
 */

#ifndef SOURCE_DIRECTORY__COMMUNICATOR_H_
#define SOURCE_DIRECTORY__COMMUNICATOR_H_

#include <string>
#include "Device.h"
#include "TcpServer.h"
using Quadcopter::Blackboard;
namespace Quadcopter {
class Communicator : public Device {
public:
	Communicator(TcpServer* tcp) :
			Device(ID_COMM, "Communicator"), tcpServer(tcp) {
	}
	string translateForeign(Blackboard::BBMessage msg);
	Blackboard::BBMessage translateLocal(string msg);
	void init(Blackboard* bb);
	void update(Blackboard *bb);
	virtual ~Communicator();
private:
	TcpServer* tcpServer;
};

}
#endif /* SOURCE_DIRECTORY__COMMUNICATOR_H_ */
