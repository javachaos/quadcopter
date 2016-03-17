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
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT "9034"   // port we're listening on

fd_set master;    // master file descriptor list
fd_set read_fds;  // temp file descriptor list for select()
int fdmax;        // maximum file descriptor number

int listener;     // listening socket descriptor
int newfd;        // newly accept()ed socket descriptor
struct sockaddr_storage remoteaddr; // client address
socklen_t addrlen;

unsigned char buf[256];    // buffer for client data
int nbytes;

char remoteIP[INET6_ADDRSTRLEN];

int yes=1;        // for setsockopt() SO_REUSEADDR, below
int i, j, rv;
struct timeval timeout;
struct addrinfo hints, *ai, *p;
unsigned char* cupdate(const unsigned char* data);
void cinit();
void cclose();

#ifdef __cplusplus
}
#endif

#endif /* C_DRIVERS_COMM_SERVER_H_ */
