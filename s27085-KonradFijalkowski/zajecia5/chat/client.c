#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv){
    char filename[100] = "/tmp/";
    FILE* newfile;
    char * str = "jajco";

    strcat(filename, argv[1]);
    printf("%s\n", filename);
    newfile = fopen(filename, "w");
    if(!newfile){
        perror("File creation failed");
        return EXIT_FAILURE;
    }
    fwrite(str, 1, 6, newfile);
    remove(filename);
    return 0;
}