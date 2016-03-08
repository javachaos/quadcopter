/*
 * OLED.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: alfred
 */

#include "OLED.h"

#include <iostream>
#include "Log.h"
#include "c_drivers/oled.h"

using namespace std;

namespace Quadcopter {

OLED::OLED() : Device("OLED") {
}

void OLED::init() {
    clog << kLogNotice << "OLED Device initialized." << endl;
    init_c();
}

void OLED::update(string data) {
    if (data.compare(prev_msg) != 0) {
        OLED::write(data);
        prev_msg = data;
    }
}

void OLED::write(string data) {
    write_str(data.c_str());
}

OLED::~OLED() {
    destroy_c();
}

}
