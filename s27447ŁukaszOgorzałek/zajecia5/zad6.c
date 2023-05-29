/* 
Zadanie: 

|> Napisz prosty program chat-u, który będzie korzystał z pliku w katalogu /tmp do przekazywania wiadomości.
Zastanów się jak to zrobić. <|
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MESSAGE_LENGTH 250
#define RELAY_FILE "/tmp/chat_relay"

void clearInputBufer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int sendMessage(FILE* messages_file, const char* message, const char* username) {
    int messageLength;
    time_t currentTime = time(NULL);
    struct tm* time_info = localtime(&currentTime);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);

    if (username != NULL)
        messageLength = fprintf(messages_file, "[%s] [%s] %s\n", timestamp, username, message);
    else
        messageLength = fprintf(messages_file, "[%s] %s\n", timestamp, message);

    fflush(messages_file);
    return messageLength;
}

int readMessage(FILE* messages_file, char* buffer) {
    int messageLength = fread(buffer, sizeof(char), MAX_MESSAGE_LENGTH, messages_file);
    if (messageLength > 0)
        buffer[messageLength - 1] = '\0';  /* Terminate string at the last read character */
    return messageLength;
}

void cleanup() {
    remove(RELAY_FILE);
}

int main() {
    FILE *writeFile, *readFile;
    char inputBuffer[MAX_MESSAGE_LENGTH + 1];  /* +1 for null terminator */
    char messageBuffer[MAX_MESSAGE_LENGTH + 1];
    char username[50];
    int messageLength;

    atexit(cleanup);

    writeFile = fopen(RELAY_FILE, "a");
    if (writeFile == NULL) {
        perror("Failed to open write file");
        return 1;
    }

    readFile = fopen(RELAY_FILE, "r");
    if (readFile == NULL) {
        perror("Failed to open read file");
        fclose(writeFile);
        return 1;
    }
    fseek(readFile, 0, SEEK_END);

    printf("Welcome to the Chat Relay Program!\n\n");
    printf("Instructions:\n");
    printf("- Enter your username when prompted.\n");
    printf("- To exit the program, enter '#exit'.\n");
    printf("- To view the chat history, enter '#history'.\n");
	printf("\t *This is currently also the only way to display messages from other users before sending yours.*\n\n");
    printf("Please enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    while (1) {
        printf("[msg] ");
        scanf("%100[^\n]", inputBuffer);
        clearInputBufer();

        if (strcmp(inputBuffer, "#exit") == 0) {
            break;
        }

        if (strcmp(inputBuffer, "#history") == 0) {
            printf("********** CHAT HISTORY **********\n");
            fseek(readFile, 0, SEEK_SET);
            while ((messageLength = readMessage(readFile, messageBuffer)) > 0) {
                if (strstr(messageBuffer, username) != NULL) {
                    printf("< %s\n", messageBuffer);
                }
            }
            printf("*********************************\n");
            memset(messageBuffer, 0, sizeof(messageBuffer));
            continue;
        }

        if (strlen(inputBuffer) > MAX_MESSAGE_LENGTH) {
            printf("Message exceeds the maximum length!\n");
            continue;
        }

        messageLength = readMessage(readFile, messageBuffer);
        if (messageLength == EOF) {
            perror("Failed to read message");
            break;
        }
        if (messageLength > 0) {
            printf("< %s\n", messageBuffer);
        }
        memset(messageBuffer, 0, sizeof(messageBuffer));

        messageLength = sendMessage(writeFile, inputBuffer, username);
        if (messageLength < 0) {
            perror("Failed to send message");
            break;
        }
        memset(inputBuffer, 0, sizeof(inputBuffer));
        fseek(readFile, 0, SEEK_END);
    }

    fclose(writeFile);
    fclose(readFile);
    return 0;
}

/*
- "clearInputBufer()" ta służy do czyszczenia bufora wejścia,
eliminując zbędne znaki nowej linii i inne znaki pozostające w buforze 
po wczytaniu danych z konsoli.

- "sendMessage()" odpowiada za zapisywanie wiadomości do pliku. 
przyjmuje wskaźnik na plik, treść wiadomości oraz nazwę użytkownika,
który wysłał wiadomość. Funkcja generuje również datę i godzinę wiadomości. 
wiadomość jest formatowana i zapisywana w pliku wraz z informacjami 
o czasie i nazwie użytkownika.

- "readMessage()" odczytuje wiadomość z pliku. Przyjmuje wskaźnik na plik 
oraz bufor, do którego zostanie zapisana odczytana wiadomość. 
funkcja odczytuje dane z pliku i zapisuje je w buforze. Na końcu 
bufor jest zamykany znakiem null, aby zakończyć ciąg znaków.

- funkcja "cleanup()" jest wywoływana przy zamykaniu programu i usuwa 
plik tymczasowy zawierający wiadomości czatu. Funkcję "atexit()" używamy
do zarejestrowania tej funkcji, aby była automatycznie wywoływana przed 
zamknięciem programu.

- "main()" to oczywiście nasza główna funkcja programu. Początkowo otwierane 
są pliki dla odczytu i zapisu. Następnie użytkownik zostaje poproszony o podanie 
nazwy użytkownika. Program przechodzi w pętlę, w której użytkownik może wprowadzać
wiadomości. Po wprowadzeniu wiadomości program odczytuje i wyświetla wcześniej wysłane
wiadomości z pliku. Jeśli wpisana wiadomość to "#exit", program kończy działanie. 
jeśli wpisana wiadomość to "#history", program wyświetla historię wiadomości. 
w przeciwnym razie wiadomość jest zapisywana do pliku. Pętla kontynuuje się do momentu 
wpisania "#exit".
*/
