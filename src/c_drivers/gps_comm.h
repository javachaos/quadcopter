#ifndef GPS_COMM_H_
#define GPS_COMM_H_
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

//NMEA SENTENCE BUFFER
char buf[NMEA_SENTENCE_LENGTH+1];
//Pointer to buffer.
char * bufp = buf;

//True if buffer is ready.
bool ready = false;
char empty[1] = {'\0'};
int gfd = 0;
int set_interface_attribs(int fd, int speed, int parity);
void set_blocking(int fd, int should_block);

#ifdef __cplusplus
extern "C" {
#endif

void gps_init();
char* getData();

#ifdef __cplusplus
}
#endif
#endif/* GPS_COMM_H_ */
