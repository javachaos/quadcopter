/*
 * comm_server.c
 *
 *  Created on: Mar 16, 2016
 *      Author:
 */
#include <comm_server.h>
#include <syslog.h>

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
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

char* cupdate(const char* d) {

    read_fd_set = active_fd_set;
    if (select (fdmax+1, &read_fd_set, NULL, NULL, &tv) < 0) {
      perror ("select");
      return 0;
    }

    char sbuf[MAX_MSG_LENGTH];
    int MSG_LEN = strlen(d)+1;

    memcpy(sbuf, d, MSG_LEN);//Copy data to send to clients into send buffer.
    if(sbuf[MSG_LEN] != '\0') {//Add null terminator if it's not there.
        sbuf[MSG_LEN] = '\0';
    }
    char* rets = 0;
    char rbuf[MAX_MSG_LENGTH];//Initialize recieve buffer.
    int i;
    for(i = 0; i <= fdmax; i++) {
        if (FD_ISSET(i, &read_fd_set)) { // we got one!!
            if (i == sockfd) {//Listen socket, add new fd to active fd set
                sin_size = sizeof their_addr;
                new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
                fcntl(new_fd, F_SETFL, O_NONBLOCK);
                if (new_fd == -1) {
                    perror("accept");
                    continue;
                } else {
                    FD_SET(new_fd, &active_fd_set); // add to the active fd set
                    if (new_fd > fdmax) {    // keep track of the max
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
                    rbuf[nbytes] = '\0';
                    rets = parse(rbuf);
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
    return rets;
}

void cclose() {
    close(sockfd);
    closelog();
}
