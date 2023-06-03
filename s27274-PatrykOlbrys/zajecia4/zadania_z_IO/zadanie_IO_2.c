#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/* ctype.h potrzebny do funkcji isprint()*/

#define BYTES_PER_GROUP 16

typedef unsigned char byte;
/* Alias o nazwie 'byte' dla typu danych unsigned char*/

int main(int argc, char *argv[]) {
    size_t i = 0;
    FILE *file;
    byte *buffer;
    size_t bytes_read;
    long offset = 0;
    
    /* Sprawdzenie liczby argumentów */
    if (argc < 2) {
        printf("Podaj nazwę pliku jako argument programu.\n");
        return 1;
    }
    
    /* Otwarcie pliku */
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return 1;
    }
    
    /* Alokacja pamięci dla bufora */
    buffer = (byte*)malloc(BYTES_PER_GROUP * sizeof(byte));
    if (buffer == NULL) {
        printf("Błąd przy alokacji pamięci.\n");
        fclose(file);
        return 1;
    }
    
    /* Wyświetlanie zawartości pliku w postaci szesnastkowej */
    printf("Loading file: %s\n\n", argv[1]);
    
    while ((bytes_read = fread(buffer, sizeof(byte), BYTES_PER_GROUP, file)) > 0) {
        /* ^ Wykonuj pętlę dopóki funkcja fread odczytuje dane z pliku
        i zwraca wartość większą niż 0 */
        printf("%08lX  ", offset);
        /* ^ Wydrukuj offset jako ośmiocyfrową liczbę szesnastkową typu long
        To jest to po lewej stronie */
        
        for (i = 0; i < bytes_read; i++) {
            printf("%02X ", buffer[i]);
            /* Wydrukuj bajt buffer jako dwucyfrową liczbę szesnastkową */
        }
        
        if (bytes_read < BYTES_PER_GROUP) {
            /* Uzupełnienie końca linii pustymi znakami dla estetycznego wyglądu */
            for (i = 0; i < BYTES_PER_GROUP - bytes_read; i++) {
                printf("   ");
            }
        }
        
        printf(" ");
        
        for (i = 0; i < bytes_read; i++) {
            if (isprint(buffer[i])) {
                /* Jeżeli znak da się wydrukować to go drukujemy */
                printf("%c", buffer[i]);
            } else if (buffer[i] == '\n' || buffer[i] == '\t' || buffer[i] == ' ') {
                /* Jeżeli bajt jest którymś z tych znaków białych
                to drukujemy kropkę */
                printf(".");
            } 
            else {
                printf("▒");
                /* Jeżeli nie, to zastępujemy tym znakiem */
            }
        }
        
        printf("\n");
        offset += bytes_read;
    }
    
    printf("\nClosing file: %s\n", argv[1]);
    
    /* Zwolnienie pamięci i zamknięcie pliku */
    free(buffer);
    fclose(file);
    
    return 0;
}
