/*
 * OLED.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: alfred
 */

#include "OLED.h"

#include <iostream>
#include "../Log.h"
#include "c_drivers/oled.h"
using namespace std;

namespace Quadcopter {

OLED::OLED() : Device("OLED") {
}

void OLED::init() {
	clog << kLogNotice << "OLED Device initialized." << endl;
}

void OLED::update(string data) {
	OLED::write(data);
}
void OLED::write(string data) {
	write_str(data.c_str());
}

OLED::~OLED() {
}

}
