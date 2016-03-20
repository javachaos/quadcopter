#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include <Blackboard.h>
#include <Constants.h>
#include <Controller.h>
using std::string;
using std::endl;
using std::clog;
using std::sig_atomic_t;
using std::ofstream;
using std::to_string;

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
	Controller *controller = new Controller();
	controller->start();
        int heartbeat = 10000;
        int h = 0;
	while (!term) {
		controller->update();
                if(--heartbeat == 0) {
                    heartbeat = 10000;
                    clog << kLogNotice << "Heartbeat " << ++h << endl;
                    controller->display("Heartbeat: " + std::to_string(h)
                      +"\n "+ controller->getDisplay());
                }
		//Sleep for 2000 microseconds before next update sequence
		struct timespec ts;
                ts.tv_sec = 0;
		ts.tv_nsec = 2000000;
		nanosleep(&ts, NULL);
	}
	controller->display("System shutting down...");
	controller->setExit(true);
	controller->update();
        delete(controller);
	closelog();
	exit(EXIT_SUCCESS);
}

