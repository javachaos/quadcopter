/*
 * Device.h
 *
 *  Created on: Feb 28, 2016
 *      Author: alfred
 */

#ifndef DEVICE_H_
#define DEVICE_H_

using namespace std;
class Device {
	virtual ~Device();
};

template<class T>
class Sensor: Device {
public:
	Sensor();
	void init() const;
	void update(const T) const;
	bool isInitialized() const;
	virtual ~Sensor();
};

#endif /* DEVICE_H_ */
