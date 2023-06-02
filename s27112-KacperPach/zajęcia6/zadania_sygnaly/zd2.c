#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>


#define FILE_PATH "/tmp/lock"

FILE *fp = NULL;

void handler (int signum) {
    printf("Wyrkyto probe uruchomienia drugiej instancji programu.\n");
}

void handler_q (int signum) {
    printf("\nExiting...\n");
    fclose(fp);
    remove(FILE_PATH);
    exit(0);
}

int main(int argc, char const *argv[])
{
    int pid = 0;
    char buffer[13];
    bzero(buffer,13);
    if (access(FILE_PATH,F_OK) == 0)
    {
        fp = fopen(FILE_PATH,"r");
        if(fread(buffer,sizeof(char),12,fp)< 0) {
            fclose(fp);
            exit(1);
        }
        pid = atoi(buffer);
        if (pid > 0)
            kill(pid,SIGUSR1);
        fclose(fp);
        exit(1);

    } else {
        pid = getpid();
        signal(SIGUSR1, handler);
        signal(SIGINT, handler_q);

        fp = fopen(FILE_PATH, "a");
        if (fprintf(fp,"%d\n",pid) < 0) {
            fclose(fp);
            exit(1);
        }
        fclose(fp);

        while (1)
        {
            sleep(1);
        }
    }
}
