#ifndef GPS_COMM_H_
#define GPS_COMM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

#define DAEMON_NAME "quadcopter"
#define PORTNAME "/dev/ttyO5"
#define NMEA_SENTENCE_LENGTH 80
#define GPS_DATA_SIZE        800 //Ten NMEA sentences

char* getData();

#ifdef __cplusplus
}
#endif
#endif/* GPS_COMM_H_ */
