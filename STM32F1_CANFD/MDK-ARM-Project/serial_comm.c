#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/select.h>
#include <signal.h>

volatile sig_atomic_t running = 1;

void handle_sigint(int sig) {
    (void)sig;
    running = 0;
}

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        return -1;
    }

    cfmakeraw(&tty);

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    tty.c_cflag |= CLOCAL | CREAD; // ignore modem controls, enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // no parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CRTSCTS; // no flow control

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // raw input
    tty.c_oflag &= ~OPOST; // raw output

    tty.c_cc[VMIN] = 1;  // blocking read until 1 char
    tty.c_cc[VTIME] = 0; // no inter-character timer

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        return -1;
    }
    return 0;
}

speed_t baud_to_constant(int baud)
{
    switch (baud) {
        case 115200: return B115200;
        case 57600: return B57600;
        case 38400: return B38400;
        case 19200: return B19200;
        case 9600: return B9600;
        case 460800: return B460800;
        default: return B115200;
    }
}

int main(int argc, char *argv[])
{
    const char *device = "/dev/ttyUSB0";
    int baud = 115200;

    if (argc >= 2) device = argv[1];
    if (argc >= 3) baud = atoi(argv[2]);

    signal(SIGINT, handle_sigint);

    int fd = open(device, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        fprintf(stderr, "Error opening %s: %s\n", device, strerror(errno));
        return 1;
    }

    speed_t spd = baud_to_constant(baud);
    if (set_interface_attribs(fd, spd) != 0) {
        close(fd);
        return 1;
    }

    printf("Opened %s at %d baud\n", device, baud);
    fflush(stdout);

    char recvbuf[2048];
    size_t recvpos = 0;

    char readbuf[512];
    char linebuf[512];

    while (running) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        int maxfd = fd > STDIN_FILENO ? fd : STDIN_FILENO;

        int rv = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (rv < 0) {
            if (errno == EINTR) continue;
            perror("select");
            break;
        }

        if (FD_ISSET(fd, &readfds)) {
            ssize_t n = read(fd, readbuf, sizeof(readbuf));
            if (n > 0) {
                // print received bytes to stdout
                fwrite(readbuf, 1, n, stdout);
                fflush(stdout);

                // append to recv buffer as text (keep safe)
                size_t copy = (size_t)n;
                if (recvpos + copy >= sizeof(recvbuf) - 1) {
                    // shift left to make room
                    size_t keep = sizeof(recvbuf)/2;
                    if (keep > recvpos) keep = recvpos;
                    memmove(recvbuf, recvbuf + recvpos - keep, keep);
                    recvpos = keep;
                }
                memcpy(recvbuf + recvpos, readbuf, copy);
                recvpos += copy;
                recvbuf[recvpos] = '\0';

                if (strstr(recvbuf, "111") != NULL) {
                    printf("\nOK\n");
                    fflush(stdout);
                    // clear buffer after detection to avoid repeated prints
                    recvpos = 0;
                    recvbuf[0] = '\0';
                }
            } else if (n == 0) {
                // EOF
            } else {
                if (errno != EINTR) perror("read");
            }
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (fgets(linebuf, sizeof(linebuf), stdin) != NULL) {
                size_t len = strlen(linebuf);
                ssize_t w = write(fd, linebuf, len);
                if (w < 0) perror("write to serial");
            } else {
                // stdin closed
                running = 0;
            }
        }
    }

    close(fd);
    printf("\nExiting\n");
    return 0;
}
