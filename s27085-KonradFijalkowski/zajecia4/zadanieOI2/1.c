#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <wchar.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>

int displayRow(FILE *file, int64_t rowAddress){
    /*alokuje tablicę dla 16 integerów*/
    unsigned char *line = malloc(16*sizeof (unsigned char));
    int charsRead;
    int i;
    wchar_t unicodeDots = 0x2592;

    if(line == NULL){
        perror("Malloc error: ");
        return -1;
    }
    /*zmienna z wartością unicode dla znaku kropek*/

    /*sprawdzam ile znaków zostaje wczytanych*/
    charsRead = fread(line, 1, 16, file);

    /*jeżeli nie ma już nic do wczytania w linii zakończ funkcję*/
    if(charsRead == 0){
        return -1;
    }

    /*wyświetlenie adresu wiersza z poprzedzającymi zerami*/
    printf("%06llX: ", rowAddress);

    /*wyświetlenie kolejnych bitów linii*/
    for(i = 0; i < charsRead; i++){
        printf("%02X ", line[i]);
    }

    /*wyświetlenie białych znaków w miejsce brakujących bajtów*/
    for(i = 0; i < (16-charsRead); i++){
        printf("   ");
    }
    for(i = 0; i< charsRead; i++){
        if(line[i] > 32 && line[i] < 127){ /*https://www.utm.edu/staff/lholder/csci201/ascii_table.pdf*/
            printf("%c", line[i]);
        }
        else{
            _setmode(_fileno(stdout), _O_U16TEXT); /*zmiana ustawienia consoli na odczytywanie znaków w UNICODE16*/
            wprintf(L"%lc", unicodeDots);
            _setmode(_fileno(stdout), _O_TEXT); /*powrót do standardowego odczytu tekstu*/
        }
    }
    free(line);
    printf("\n");
    return charsRead;
}


int main(int argc, char** argv){
    FILE *file;
    int64_t rowAddress = 0; /*int64 to jest 6 miejsc na liczbę w systemie heksadecymalnym*/

    /*jeżeli nie podano dwóch argumentów oznaccza to, że nie mamy nazwy pliku do otworzenia*/
    if(argc < 2){
        printf("File name is missing");
        exit(EXIT_FAILURE);
    }
    file = fopen(argv[1], "r");

    /*sprawdzam, czy plik został poprawnie otwarty*/
    if(file == NULL) {
        perror("Unable to open text file");
        return -1;
    }
    /*rozpoczynam wyświetlanie pliku wiersz po wierszu z tytułem i stopką*/
    printf("Loading file: %s\n", argv[1]);
    while(displayRow(file, rowAddress) != -1){
        rowAddress += 16; /*kolejne adresy wierszy*/
    }
    printf("Closing file: %s\n", argv[1]);
    fclose(file);
    return 0;
}
