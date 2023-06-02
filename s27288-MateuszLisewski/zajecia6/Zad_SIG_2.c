#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

extern int kill(pid_t pid, int sig); 

#define LOCK_FILE "/tmp/lock"

void handleUSR1(int sig);
void handleCTRLC(int sig);

int main() {
    int fd;
    char pid_buf[16];
    pid_t pid;
    FILE* lock_file;

    fd = open(LOCK_FILE, O_RDWR | O_CREAT | O_EXCL, 0666);
    if (fd == -1) {
        ssize_t bytes_read = 0;
        fd = open(LOCK_FILE, O_RDWR);
        if (fd == -1) {
            perror("Blad otwierania pliku .lock");
            exit(1);
        }

        bytes_read = read(fd, pid_buf, sizeof(pid_buf) - 1);
        if (bytes_read <= 0) {
            perror("Blad odczytu pliku .lock");
            exit(1);
        }
        pid_buf[bytes_read] = '\0';

        pid = atoi(pid_buf);
        kill(pid, SIGUSR1);

        close(fd);
        exit(0);
    }

    pid = getpid();
    lock_file = fopen(LOCK_FILE, "w");
    if (lock_file == NULL) {
        perror("Blad otwierania pliku .lock");
        exit(1);
    }
    fprintf(lock_file, "%d", pid);
    fclose(lock_file);

    signal(SIGUSR1, handleUSR1);
    signal(SIGINT, handleCTRLC);

    while (1) {
        sleep(1);
    }

    return 0;
}

void handleUSR1(int sig) {
    printf("Wykryto próbę uruchomienia drugiej instancji programu.\n");
}

void handleCTRLC(int sig) {
    remove(LOCK_FILE);
    exit(0);
}
