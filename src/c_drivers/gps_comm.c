#include "gps_comm.h"

//Setup global storage for 10 NMEA sentences.
char GPSData[GPS_DATA_SIZE+1];
bool ready = false;
char empty[1] = {'\0'};

void cinit() {
    openlog (DAEMON_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
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
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
        if (tcsetattr (fd, TCSANOW, &tty) != 0)
            syslog(LOG_NOTICE, "COMM_GPS: error %d setting term attributes", errno);
}

int
setup() {
    int fd = open (PORTNAME, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        syslog(LOG_NOTICE, "COMM_GPS: error %d opening %s: %s", errno, PORTNAME, strerror (errno));
        return fd;
    }

    set_interface_attribs (fd, B9600, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                    // set no blocking

    return fd;
}

char* getData() {

    int fd = setup();
    char * p = GPSData;
    char * end = &GPSData[sizeof(GPSData)];
    if(p >= end) {
        p = GPSData;
        GPSData[GPS_DATA_SIZE+1] = '\0';
        ready = true;
    } else {
        char buf [NMEA_SENTENCE_LENGTH];
        int n = read (fd, buf, NMEA_SENTENCE_LENGTH);
        strncpy(p,buf, n);
        p += NMEA_SENTENCE_LENGTH;
    }

    if(ready) {
        ready = false;
        return GPSData;
    }
    return empty;
}
