/*
 * OLED.h
 *
 *  Created on: Feb 29, 2016
 *      Author: alfred
 */

#ifndef DEVICES_OLED_H_
#define DEVICES_OLED_H_

#include <string>
#include "Device.h"
#include "Blackboard.h"
using namespace std;
namespace Quadcopter {

extern "C" void write_str(const char*);

class OLED: public Device {
public:
	OLED() :
			Device(ID_OLED, "OLED") {
	}
	void update(shared_ptr<Blackboard> bb);
	void init(shared_ptr<Blackboard> bb);
	~OLED();
	void write(string data);
private:
	string prev_msg;
};
}
#endif /* DEVICES_OLED_H_ */

