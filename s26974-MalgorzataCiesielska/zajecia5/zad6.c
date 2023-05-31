#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <signal.h>

int fd;
int wd;
int shouldExit = 0;
char username[25];
int firstRefresh = 1;
int refreshInProgress = 0;

void signalHandler(int sig) { /*handles interrupt signal and stops inotify from waiting for file modifications*/
    if (sig == 15) {
        inotify_rm_watch(fd, wd);
        close(fd);
        exit(0);
    }
}

void refreshChat() { /*method that prints out entire chat history*/
    FILE * filePtr;
    char c;
    system("clear"); /*clears console*/
    if (access("/tmp/chat", F_OK) == 0) { /*checks if file exists*/
        if (firstRefresh) { /*will only print if this is the first time refreshing the chat*/
            printf("Chat history:\n");
        }
        filePtr = fopen("/tmp/chat", "r");
        if (filePtr == NULL) {
            printf("Could not open file");
            return;
        }
        while ((c = getc(filePtr)) != EOF) {
            printf("%c", c);   
        }
        fclose(filePtr);
    }
    if (firstRefresh) {
        printf("\nYou can now chat! To exit, type ':q'\n");
        firstRefresh = 0;
    }
    printf("%s:", username);
    refreshInProgress = 0;
}

void *readThread(void *vargp) {
    struct inotify_event *event;
    fd = inotify_init(); /*inotify allows us to react to changes in files*/
    wd = inotify_add_watch(fd, "/tmp/chat", IN_MODIFY); /*we add watch to the chat file*/
    event = (struct inotify_event*) malloc(sizeof(struct inotify_event));
    if (event == NULL) {
        printf("Memory allocation failed");
        return;
    }
    signal(SIGTERM, signalHandler); /*handles interrupt signal from main thread (the one with the write loop)*/
    while (!shouldExit) {
        read(fd, event, 1000); /*waits for changes to file (if we don't send interrupt signal it will wait indefinitely)*/
        if (event->mask & IN_MODIFY) { /*checks if file was modified*/
            refreshChat();
        }
    }
    return NULL;
}

void writeLoop() {
    FILE * filePtr;
    while (!shouldExit) {
        char input[256];
        scanf("%255s", input);
        if (strcmp(input, ":q") == 0) { /*strcmp compares actual string content instead of pointers*/
            shouldExit = 1;
            continue;
        }
        filePtr = fopen("/tmp/chat", "a");
        if (filePtr == NULL) {
            printf("Could not open file");
            return;
        }
        fprintf(filePtr, "%s:%s\n", username, input);
        fclose(filePtr);
        refreshInProgress = 1;
        while (refreshInProgress) { /*necessary so write loop and reading thread don't print
                                     and scan from console simultaneously*/
            sleep(1);
        }
    }
}

int main() {
    pthread_t readThreadPtr;

    printf("Hi, welcome to chat! Please enter username: ");
    scanf("%24s", username);

    pthread_create(&readThreadPtr, NULL, readThread, NULL); /*creates a separate thread for reading from file*/
    refreshChat();
    writeLoop(); /*starts loop for reading user input*/
    pthread_kill(readThreadPtr, 15); /*after write loop exits, reading thread is killed*/
    pthread_join(readThreadPtr, NULL); /*waits for reading thread to close properly*/
    return 0;
}