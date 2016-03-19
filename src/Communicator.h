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
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>

namespace Quadcopter {

extern "C" char* cupdate(const char*);
extern "C" void cinit();
extern "C" void cclose();

class Communicator : public Device {
public:
    Communicator() :
        Device(ID_COMM, "Communicator") {
    }
    void init(Blackboard* bb);
    void update(Blackboard *bb);
    virtual ~Communicator();
private:
    void addReply(char* reply, Blackboard* bb);
};

}
#endif /* SOURCE_DIRECTORY__COMMUNICATOR_H_ */
