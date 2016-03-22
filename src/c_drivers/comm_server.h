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
#include "parse.h"

#define PORT "22200"
#define DAEMON_NAME "quadcopter"
#define BACKLOG         10
#define MAX_MSG_SIZE    32 //In bytes
#define MAX_FDS         1024
#define MAX_DATA_SIZE   21 //In bytes
#define BITS_PER_CHAR   8
#define DATA_OFFSET     11

typedef struct __attribute__((__packed__)) {
    char msg_len;
    char to;
    char from;
    unsigned long timestamp;
    char payload[MAX_DATA_SIZE];
} Data;

char* packMessage(const Data data);
const Data unpackMessage(const char* msg);
const Data cupdate(const Data data);
void cinit();
void cclose();

#ifdef __cplusplus
}
#endif

#endif /* C_DRIVERS_COMM_SERVER_H_ */
