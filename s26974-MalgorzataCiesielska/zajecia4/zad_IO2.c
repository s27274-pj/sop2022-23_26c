#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    char fileName[255];
    FILE * filePtr;
    unsigned char line[16]; /*needs to be unsigned so values are stored correctly*/
    int i;
    int countOfChars;
    int countOfLines = 0;
    printf("Please input name of file: ");
	scanf("%254s", fileName);
    filePtr = fopen(fileName, "r");
    do {
        countOfChars = fread(&line, sizeof(char), 16, filePtr); /*tries to read 16 chars from file into line[16] array and 
                                                                assignes number of characters actually read to countOfChars*/
        printf("%07X0  ", countOfLines++);  /*prints line number (followed by two spaces for aesthetics)*/
        for (i = 0; i < countOfChars; i++) {
            printf("%02X ", line[i]);  /*prints each char in line formatted to hex and followed by a space*/
        }
        if (countOfChars < 16) {  /*fills the rest of the line with spaces if there are less than 16 chars (again, for aesthetics)*/
            for (i = 0; i < 16 - countOfChars; i++) {
                printf("   ");
            }
        }
        printf(" ");
        for (i = 0; i < countOfChars; i++) /*prints the char if printable, prints '..' is it's a newline character
                                           and '▒' if it's unprintable*/
        {
            if (isprint(line[i])) {
                printf("%c", line[i]);
            } else if (line[i] == '\n') {
                printf("..");
            } else {
                printf("▒");
            }
        }
        printf("\n");
    } while (!feof(filePtr)); /*feof tells us whether we've reach end of file or not*/
    fclose(filePtr);
    return 0;
}