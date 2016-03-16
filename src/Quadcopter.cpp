//============================================================================
// Name        : Quadcopter.cpp
// Author      : Alfred Laderoute
// Version     : v0.1
// Copyright   : LGPLv3
// Description : Quadcopter service in C++, Ansi-style
//============================================================================

#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Blackboard.h"
#include "Constants.h"
#include "Controller.h"
#include "OLED.h"
#include "Motor.h"
#include "Communicator.h"

using std::string;
using std::endl;
using std::clog;
using std::sig_atomic_t;
using std::ofstream;
using namespace Quadcopter;

static void create_pidfile(void);
volatile sig_atomic_t term;

static void signal_handler(int sig) {

	switch (sig) {
	case SIGINT:
		clog << kLogNotice << "Received SIGINT." << endl;
		break;
	case SIGHUP:
		clog << kLogNotice << "Received SIGHUP Exiting." << endl;
		term = true;
		break;
	case SIGTERM:
		clog << kLogNotice << "Received SIGTERM Exiting." << endl;
		term = true;
		break;
	default:
		break;
	}
}

static void create_pidfile(void) {
	unlink(PIDFILE);
	ofstream outfile(PIDFILE);
	outfile << getpid() << endl;
	outfile.close();
}

int main(int argc, char* argv[]) {

	/* Our process ID and Session ID */
	pid_t pid, sid;

	/* Fork off the parent process */
	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	/* If we got a good PID, then
	 we can exit the parent process. */
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	/* Change the file mode mask */
	umask(0);

	/* Open syslog */
	clog.rdbuf(new Log(DAEMON_NAME, LOG_LOCAL0));
	clog << kLogNotice << "Program started by User: " << getuid() << endl;

	/* Create a new SID for the child process */
	sid = setsid();
	if (sid < 0) {
		syslog(LOG_ERR, "SID < 0");
		exit(EXIT_FAILURE);
	}

	/* Change the current working directory */
	if ((chdir("/")) < 0) {
		clog << kLogNotice << "Failed to change the cwd." << endl;
		exit(EXIT_FAILURE);
	}

	/* Close out the standard file descriptors */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	create_pidfile();

	std::signal(SIGINT, signal_handler);
	std::signal(SIGHUP, signal_handler);
	std::signal(SIGTERM, signal_handler);

	/* Daemon-specific initialization goes here */
	Blackboard *bb = new Blackboard();
	Controller *controller = new Controller(bb);
	OLED *oled = new OLED;
	controller->addDevice(oled);
	Communicator *comms = new Communicator;
	controller->addDevice(comms);
	Motor *m1 = new Motor(ID_MOTOR1, MOTOR_1);
	Motor *m2 = new Motor(ID_MOTOR2, MOTOR_2);
	Motor *m3 = new Motor(ID_MOTOR3, MOTOR_3);
	Motor *m4 = new Motor(ID_MOTOR4, MOTOR_4);
	controller->addDevice(m1);
	controller->addDevice(m2);
	controller->addDevice(m3);
	controller->addDevice(m4);

	controller->start();
	oled->write("Controller started.");
	bb->activate();
	while (!term) {
		controller->update();
	}
	oled->write("System shutting down...");
	controller->setExit(true);
	controller->update();
	controller->~Controller();
	closelog();
	exit(EXIT_SUCCESS);
}

