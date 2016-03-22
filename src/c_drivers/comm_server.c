/*
 * comm_server.c
 *
 *  Created on: Mar 16, 2016
 *      Author:
 */
#include <comm_server.h>
#include <syslog.h>
#include <base64.h>

int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
int fdmax = 0;
struct addrinfo hints, *servinfo, *p;
struct sockaddr_storage their_addr; // connector's address information
socklen_t sin_size;
struct sigaction sa;
int yes=1;
struct timeval tv = {0, 2000};
fd_set active_fd_set, read_fd_set;
char gmsg_buff[MAX_MSG_SIZE]; // Message buffer.
char s[INET6_ADDRSTRLEN];
int rv;

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

char* packMessage(const Data data) {
    char *p = gmsg_buff;                   // Set a pointer to our msg.
    memcpy(p, &data.msg_len, sizeof(char));// Copy our message length to the message.
    p += sizeof(char);                     // advance msg pointer
    memcpy(p, &data.to, sizeof(char));     // Copy our to byte
    p += sizeof(char);                     // advance msg pointer
    memcpy(p, &data.from, sizeof(char));   // Copy our from byte
    p+= sizeof(char);                      // advance msg pointer
    memcpy(p, &data.timestamp, sizeof(unsigned long));// Copy our timestamp
    p += sizeof(unsigned long);            // advance msg pointer
    memcpy(p, &data.payload, MAX_DATA_SIZE);// Copy our payload string
    gmsg_buff[MAX_DATA_SIZE] = '\0';             // Add null terminator byte
    p = NULL;                              // Set pointer to null

    return gmsg_buff;                      // return global msg buffer.
}

const Data unpackMessage(const char* msg) {
    unsigned long timestamp = 0;
    char tmp_msg[MAX_MSG_SIZE];            // Read msg into a local mutable copy.
    memcpy(tmp_msg, &msg, MAX_MSG_SIZE);   //
    char payload[MAX_DATA_SIZE];           // Initialize payload array.
    const char * t = &tmp_msg[DATA_OFFSET];// Set pointer to the data offset within our local copy of msg.
    char * p = &payload[0];                // Set pointer to the start of our payload.

    timestamp += (double) tmp_msg[3];      // Convert our unsigned long portion of the string into an unsigned long.
    timestamp  = timestamp << BITS_PER_CHAR;// Bit shift left by 8,
    timestamp += (double) tmp_msg[4];      // Add next byte,
    timestamp  = timestamp << BITS_PER_CHAR;// Bit shift left by 8,
    timestamp += (double) tmp_msg[5];      // Add next byte,
    timestamp  = timestamp << BITS_PER_CHAR;// Bit shift left by 8,
    timestamp += (double) tmp_msg[6];      // Add last byte
    int i;

    for(i = 0; i < MAX_DATA_SIZE; ++i) {
        memcpy(p, t++, sizeof(char));      // Fill the payload string.
    }
    payload[MAX_DATA_SIZE] = '\0';         // Null terminate the payload.
    Data d = { tmp_msg[0],                 // Place data into packed struct.
               tmp_msg[1],
               tmp_msg[2],
               timestamp,
               {*payload}
             };
   return d;                               // Return data.
}

void cinit() {
    openlog (DAEMON_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        syslog(LOG_NOTICE, "COMM_SERVER: failed to bind.\n");
        return;
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        return;
    }

    /* Initialize the set of active sockets. */
    FD_ZERO (&active_fd_set);
    FD_SET (sockfd, &active_fd_set);
    fdmax = sockfd;
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    syslog(LOG_NOTICE, "COMM_SERVER: waiting for connections...\n");
}

/**
 * Accept and handle client connections asychroniously.
 * 1. Packs data payload into 32 byte messages.
 * 2. Accepts new connection if socket has a waiting
 *    connection adds client to file descriptor set.
 * 3. Closes client file descriptors who HUPed.
 * 4. If clients are connected sends 32 data payload.
 */
const Data cupdate(const Data data) {
    char* d = packMessage(data);        //Pack data into char*
    read_fd_set = active_fd_set;
    if (select (fdmax+1, &read_fd_set, NULL, NULL, &tv) < 0) {
      perror ("select");
      return data;
    }

    char sbuf[MAX_MSG_SIZE];            //Initialize send buffer.
    Base64encode(sbuf, d, MAX_MSG_SIZE);//Encode send buffer data to Base64.
    char* rets = 0;                     //Setup return string.
    char rbuf[MAX_MSG_SIZE];            //Initialize recieve buffer.
    int i;
    for(i = 0; i <= fdmax; i++) {
        if (FD_ISSET(i, &read_fd_set)) {// we got one!!
            if (i == sockfd) {          //Listen socket, add new fd to active fd set
                sin_size = sizeof their_addr;
                new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
                fcntl(new_fd, F_SETFL, O_NONBLOCK);
                if (new_fd == -1) {
                    perror("accept");
                    continue;
                } else {
                    FD_SET(new_fd, &active_fd_set); // add to the active fd set
                    if (new_fd > fdmax) {           // keep track of the max
                        fdmax = new_fd;
                    }
                    syslog(LOG_NOTICE, "COMM_SERVER: new connection from %s on "
                        "socket %d\n",
                    inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr*)&their_addr),s, sizeof s),
                    new_fd);
                    if (send(new_fd, sbuf, sizeof sbuf, 0) == -1) {
                        perror("send");
                    }
                }
            } else {//Handle client data from active socket.
                int nbytes;
                if ((nbytes = recv(i, rbuf, sizeof(rbuf), 0)) <= 0) {
                    // got error or connection closed by client
                    if (nbytes == 0) {
                        // connection closed
                        syslog(LOG_NOTICE, "COMM_SERVER: socket %d hung up.\n", i);
                    } else {
                        perror("recv");
                    }
                    close(i);
                    FD_CLR(i, &active_fd_set); // remove from active fd set
                } else {
                    Base64decode(rets, rbuf);
                    syslog(LOG_NOTICE, "COMM_SERVER: recieved %d bytes from socket %d.\n", nbytes, i);
                    syslog(LOG_NOTICE, "COMM_SERVER: %s", rets);
                    // we got some data from a client
                    int j;
                    for(j = 0; j <= fdmax; j++) {
                        // send data to all active fd's
                        if (FD_ISSET(j, &active_fd_set)) {
                            // except the listener and ourselves
                            if (j != sockfd && j != i) {
                                if (send(j, sbuf, sizeof sbuf, 0) == -1) {
                                    perror("send");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return unpackMessage(rets);
}

void cclose() {
    close(sockfd);
    closelog();
}
