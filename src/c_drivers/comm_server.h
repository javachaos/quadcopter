/*
 * comm_server.h
 *
 *  Created on: Mar 17, 2016
 *      Author: fred
 */

#ifndef C_DRIVERS_COMM_SERVER_H_
#define C_DRIVERS_COMM_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define PORT "22200"
#define DAEMON_NAME "quadcopter"
#define BACKLOG        10
#define MAX_MSG_LENGTH 256
#define MAX_FDS        1024
int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
int fdmax = 0;
struct addrinfo hints, *servinfo, *p;
struct sockaddr_storage their_addr; // connector's address information
socklen_t sin_size;
struct sigaction sa;
int yes=1;
struct timeval tv = {0, 2000};
fd_set active_fd_set, read_fd_set;

char s[INET6_ADDRSTRLEN];
int rv;
char* cupdate(const char* data);
void cinit();
void cclose();

#ifdef __cplusplus
}
#endif

#endif /* C_DRIVERS_COMM_SERVER_H_ */
