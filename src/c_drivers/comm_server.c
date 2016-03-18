/*
 * comm_server.c
 *
 *  Created on: Mar 16, 2016
 *      Author:
 */
#include <comm_server.h>
#include <syslog.h>

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}


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

//    sa.sa_handler = sigchld_handler; // reap all dead processes
//    sigemptyset(&sa.sa_mask);
//    sa.sa_flags = SA_RESTART;
//    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
//        perror("sigaction");
//        syslog(LOG_NOTICE, "COMM_SERVER: stop signal recieved.\n");
//        return;
//    }
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    syslog(LOG_NOTICE, "COMM_SERVER: waiting for connections...\n");
}

char* cupdate(const char* d) {

    sin_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
        perror("accept");
        return 0;
    }

    inet_ntop(their_addr.ss_family,
        get_in_addr((struct sockaddr *)&their_addr),
        s, sizeof s);
    syslog(LOG_NOTICE, "COMM_SERVER: new connection from %s.\n", s);
    send(new_fd, d, sizeof d, MSG_DONTWAIT);
    //if (!fork()) { // this is the child process
    //    if (send(new_fd, "Quadcopter Responce...", 13, 0) == -1) {
    //        perror("send");
    //        syslog(LOG_NOTICE, "COMM_SERVER: failed to Send.\n");
    //    }
    //    close(new_fd);
    //    exit(0);
    //}
    close(new_fd);
}

void cclose() {
    close(sockfd);
    closelog();
}
