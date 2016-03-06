/*
 * Device.h
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#include <string>

#ifndef DEVICE_H_
#define DEVICE_H_

using std::string;
namespace Quadcopter {

class Device {
	public:
		Device(string n) : name(n) , isInit(true) {}
		bool isInitialized() { return isInit; }
		virtual void init() = 0;
		string getName() const { return name; }
		virtual void update(string value) = 0;
		virtual ~Device();
	private:
		string name;
		bool isInit;
};
inline Device::~Device() {}
}
#endif /* DEVICE_H_ */
