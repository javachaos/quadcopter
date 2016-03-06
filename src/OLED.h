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

extern "C" void write_str(const char*);

using namespace std;
namespace Quadcopter {

class OLED : public Device {
public:
	OLED();
	void update(string data);
	void init();
	~OLED();
private:
	void write(string data);
};
}
#endif /* DEVICES_OLED_H_ */

