#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 1000
#define FILE_PATH "/tmp/chat_messages.txt"

void write_message(const char* message) {
    FILE* file;
    
    file = fopen(FILE_PATH, "a");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku by zapisac wiadomosc.\n");
        exit(1);
    }
    
    fprintf(file, "%s\n", message);
    fclose(file);
}

void read_messages() {
    FILE* file;
    char message[MAX_MESSAGE_LENGTH];
    
    file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku by odczytac wiadomosc.\n");
        exit(1);
    }
    
    while (fgets(message, MAX_MESSAGE_LENGTH, file) != NULL) {
        printf("%s", message);
    }
    
    fclose(file);
}

int main() {
    char message[MAX_MESSAGE_LENGTH];
    
    while (1) {
        printf("Wpisz wiadomosc ('q' by wyjsc): ");
        fgets(message, MAX_MESSAGE_LENGTH, stdin);
        
        if (strcmp(message, "q\n") == 0) {
            break;
        }
        
        write_message(message);
        read_messages();
    }
    
    return 0;
}
