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
#include "Constants.h"

using namespace std;

namespace Quadcopter {

void OLED::init() {
    clog << kLogNotice << "OLED Device initialized." << endl;
    init_c();
}

void OLED::update(Blackboard *bb) {
    Blackboard::BBMessage empty;
    Blackboard::BBMessage data = bb->checkForMessage(getId());
    if(data == empty) {
        string datum = data.msg;
        if (!datum.empty() && datum.compare(prev_msg) != 0) {
            OLED::write(datum);
            prev_msg = datum;
        }
    }
}

void OLED::write(string data) {
    write_str(data.c_str());
}

OLED::~OLED() {
    destroy_c();
}

}
