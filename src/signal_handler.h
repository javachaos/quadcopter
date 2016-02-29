/*
 * signal_handler.h
 *
 *  Created on: Feb 29, 2016
 *      Author: alfred
 */

#ifndef SIGNAL_HANDLER_H_
#define SIGNAL_HANDLER_H_

#include <syslog.h>
#include <signal.h>
#include "constants.h"
using namespace std;
extern volatile sig_atomic_t term;

void signal_handler(int sig) {

    switch(sig) {
        case SIGHUP:
        	std::clog << kLogNotice << "Received SIGHUP signal." << std::endl;
            break;
        case SIGTERM:
        	std::clog << kLogNotice << "Received SIGTERM signal." << std::endl;
            term = true;
            exit(0);
            break;
        default:
        	std::clog << kLogNotice << "Unhandled signal." << std::endl;
            break;
    }
}
#endif /* SIGNAL_HANDLER_H_ */
