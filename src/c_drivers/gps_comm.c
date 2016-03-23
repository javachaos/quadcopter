#include "gps_comm.h"

void gps_init() {
    openlog (DAEMON_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    int fd = open (PORTNAME, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        syslog(LOG_NOTICE, "COMM_GPS: error %d opening %s: %s", errno, PORTNAME, strerror (errno));
        return;
    }

    set_interface_attribs (fd, B9600, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                  // set no blocking
    bufp = buf;//Set buffer pointer to start of the buffer.
    gfd = fd;  //Set the global file descriptor.
    syslog(LOG_NOTICE, "COMM_GPS: GPS initialized.\n");
}

int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                syslog(LOG_NOTICE, "COMM_GPS: error %d from tcgetattr", errno);
                return -1;
        }
        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);
        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;
        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                syslog(LOG_NOTICE, "COMM_GPS: error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void
set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                syslog(LOG_NOTICE, "COMM_GPS: error %d from tggetattr", errno);
                return;
        }
        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 1;            // 0.1 seconds read timeout
        if (tcsetattr (fd, TCSANOW, &tty) != 0)
            syslog(LOG_NOTICE, "COMM_GPS: error %d setting term attributes", errno);
}

// Get next valid NMEA Sentence. 
// Returns empty string until a valid sentence is constructed.
char* getData() {
    if(buf[0] == '$') {
        ready = true;
    } else {
        int n = read (gfd, bufp++, sizeof(char));
        if(n < 1) {
          syslog(LOG_NOTICE, "COMM_GPS: read error.");
          return empty;
        }
    }

    if(ready) {
        ready = false;
        bufp = buf;
        return buf;
    }
    return empty;
}
