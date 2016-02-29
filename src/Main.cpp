//============================================================================
// Name        : Quadcopter.cpp
// Author      : Alfred Laderoute
// Version     : v0.1
// Copyright   : LGPLv3
// Description : Quadcopter service in C++, Ansi-style
//============================================================================

#include <stdlib.h>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <iostream>

#include "Controller.h"
#include "Log.h"

using namespace std;

#define DAEMON_NAME "quadcopter"
#define CWD "/opt/" + DAEMON_NAME

int main(void) {

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
	//openlog(DAEMON_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
	std::clog.rdbuf(new Log(DAEMON_NAME, LOG_LOCAL0));
	syslog(LOG_INFO, "Program started by User %d", getuid());
	/* Create a new SID for the child process */
	sid = setsid();
	if (sid < 0) {
		//syslog(LOG_ERR, "SID < 0");
		exit(EXIT_FAILURE);
	}

	/* Change the current working directory */
	if ((chdir("/")) < 0) {
		//syslog(LOG_ERR, "Failed to change the cwd.");
		exit(EXIT_FAILURE);
	}

	/* Close out the standard file descriptors */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	/* Daemon-specific initialization goes here */
	Controller *controller = new Controller;
	controller->start();

	closelog();
	exit(EXIT_SUCCESS);
}

