/*
 * Communicator.h
 *
 *  Created on: Mar 16, 2016
 *      Author: fred
 */

#ifndef SOURCE_DIRECTORY__COMMUNICATOR_H_
#define SOURCE_DIRECTORY__COMMUNICATOR_H_

#include "Constants.h"
#include "Device.h"

namespace Quadcopter {

extern "C" unsigned char* cupdate(const unsigned char*);
extern "C" void cinit();
extern "C" void cclose();
extern "C" unsigned int pack(unsigned char *buf, char *format, ...);
extern "C" void unpack(unsigned char *buf, char *format, ...);

class Communicator : public Device {
public:
	Communicator() :
			Device(ID_COMM, "Communicator") {
	}
	void init(Blackboard* bb);
	void update(Blackboard *bb);
	virtual ~Communicator();
private:
};

}
#endif /* SOURCE_DIRECTORY__COMMUNICATOR_H_ */
