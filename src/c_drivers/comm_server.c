/*
 * comm_server.c
 *
 *  Created on: Mar 16, 2016
 *      Author: fred
 */
#include <comm_server.h>

void cinit() {
	FD_ZERO(&master);    // clear the master and temp sets
	FD_ZERO(&read_fds);
	// get us a socket and bind it
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
	    fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
	    //exit(1);
	    return;
	}
    for(p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) {
            continue;
        }

        // lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    // if we got here, it means we didn't get bound
    if (p == NULL) {
        fprintf(stderr, "selectserver: failed to bind\n");
        //exit(2);
        return;
    }

    freeaddrinfo(ai); // all done with this
    // listen
    if (listen(listener, 10) == -1) {
        perror("listen");
        //exit(3);
        return;
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

unsigned char* cupdate(const unsigned char* data) {
	timeout.tv_sec = 0;
	timeout.tv_usec = 2000;
    read_fds = master; // copy it
    if (select(fdmax+1, &read_fds, NULL, NULL, &timeout) == -1) {
        perror("select");
        return 0;
    }

    // run through the existing connections looking for data to read
    for(i = 0; i <= fdmax; i++) {
        if (FD_ISSET(i, &read_fds)) { // we got one!!
            if (i == listener) {
                // handle new connections
                addrlen = sizeof remoteaddr;
                newfd = accept(listener,
                    (struct sockaddr *)&remoteaddr,
                    &addrlen);

                if (newfd == -1) {
                    perror("accept");
                } else {
                    FD_SET(newfd, &master); // add to master set
                    if (newfd > fdmax) {    // keep track of the max
                        fdmax = newfd;
                    }
                    printf("selectserver: new connection from %s on "
                        "socket %d\n",
                        inet_ntop(remoteaddr.ss_family,
                            get_in_addr((struct sockaddr*)&remoteaddr),
                            remoteIP, INET6_ADDRSTRLEN),
                        newfd);
                }
            } else {
                 // handle data from a client
                 if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                     // got error or connection closed by client
                     if (nbytes == 0) {
                         // connection closed
                         printf("selectserver: socket %d hung up\n", i);
                     } else {
                         perror("recv");
                     }
                     close(i); // bye!
                     FD_CLR(i, &master); // remove from master set
                 } else {
                     for(j = 0; j <= fdmax; j++) {
                         if (FD_ISSET(j, &master)) {
                             // except the listener and ourselves
                             if (j != listener && j != i) {
                            	 if(data > 0) {
                            	     size_t sent = send(j,data,sizeof data, 0);
                            	     if(sent <= 0) {
                            	         perror("send");
                            	     }
                            	 }
                             }
                         }
                     }
                     return buf;
                 }
             } if(data > 0) {
            	size_t sent = send(i,data,sizeof data, 0);
            	if(sent <= 0) {
                    perror("send");
            	}
            }
         }
     }
    return 0;
}

void cclose() {
	int i;
	for(i = 0; i <= fdmax; i++) {
	    close(i);
	    shutdown(i, 2);
	    FD_CLR(i, &master);
	    FD_CLR(i, &read_fds);
	}
	FD_ZERO(&master);    // clear the master and temp sets
	FD_ZERO(&read_fds);
}



