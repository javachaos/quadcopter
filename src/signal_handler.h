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
        case SIGINT:
    	    break;
        case SIGHUP:
            break;
        case SIGTERM:
            term = true;
            break;
        default:
            break;
    }
}
#endif /* SIGNAL_HANDLER_H_ */
