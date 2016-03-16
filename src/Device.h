/*
 * Device.h
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#ifndef DEVICE_H_
#define DEVICE_H_
#include <string>
#include "Blackboard.h"
using std::string;
namespace Quadcopter {

class Device {
public:
	Device(int id, string n) :
			name(n), isInit(true), id(id) {
	}
	bool isInitialized() {
		return isInit;
	}
	virtual void init(Blackboard *bb) = 0;
	string getName() const {
		return name;
	}
	int getId() const {
		return id;
	}
	virtual void update(Blackboard *bb) = 0;
	virtual ~Device();
private:
	string name;
	int id;
	bool isInit;
};
inline Device::~Device() {
}
}
#endif /* DEVICE_H_ */
