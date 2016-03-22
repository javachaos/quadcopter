/*
 * Communicator.h
 *
 *  Created on: Mar 16, 2016
 *      Author: fred
 */

#ifndef SOURCE_DIRECTORY__COMMUNICATOR_H_
#define SOURCE_DIRECTORY__COMMUNICATOR_H_

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "lzma.h"
#include "Constants.h"
#include "Device.h"
#include "c_drivers/comm_server.h"
#include "c_drivers/parse.h"

namespace Quadcopter {

extern "C" bool parse(const char* s);
extern "C" const Data cupdate(const Data d);
extern "C" void cinit();
extern "C" void cclose();

class Communicator : public Device {
public:
    Communicator() :
        Device(ID_COMM, "Communicator") {
    }
    void init(Blackboard* bb);
    void update(Blackboard *bb);
    string compressWithLzma(const std::string& in, int level);
    string decompressWithLzma(const std::string& in);
    virtual ~Communicator();
private:
    void addReply(const Data reply, Blackboard* bb);
    bool validateData(const Data reply);
};

}
#endif /* SOURCE_DIRECTORY__COMMUNICATOR_H_ */
