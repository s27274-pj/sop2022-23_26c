#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 16

void print_hex(char *buffer, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%02X ", (unsigned char)buffer[i]);
    }
}

void print_text(char *buffer, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            printf("%c", buffer[i]);
        } else {
            printf(".");
        }
    }
}

void print_hexdump(FILE *file) {
    int address = 0;
    char buffer[MAX_LINE_LENGTH];
    int bytes_read;
    int i;

    while ((bytes_read = fread(buffer, 1, MAX_LINE_LENGTH, file)) > 0) {
        printf("%08X  ", address);

        print_hex(buffer, bytes_read);

        if (bytes_read < MAX_LINE_LENGTH) {
            int padding = MAX_LINE_LENGTH - bytes_read;
            for (i = 0; i < padding * 3; i++) {
                printf(" ");
            }
        }

        printf(" ");

        print_text(buffer, bytes_read);

        printf("\n");

        address += MAX_LINE_LENGTH;
    }

    printf("\nClosing file...\n");
}

int main(int argc, char *argv[]) {
    FILE *file;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    printf("Loading file: %s\n\n", argv[1]);
    print_hexdump(file);

    fclose(file);

    return 0;
}

/*
dzieje się tutaj dość sporo rzeczy, więc może od początku:

definiujemy stałą "MAX_LINE_LENGTH", która będzie określać maksymalną długość linii 
wyświetlanych w heksadecymalnym zrzucie pliku.

funkcja "print_hex()" odpowiada za wypisanie wartości w postaci heksadecymalnej
(trzeba pamiętać o odpowiednim formatowaniu i zrzutowaniu do unsigned char, aby zapewnić 
poprawne wypisanie wartości bajtu w formacie heksadecymalnym).

"print_text()" wypisuje znaki jako tekst, zastępując te, które nie mieszczą się w przedziale
od 32 do 126 kropkami.

"print_hexdump()" wykonuje właściwe zadanie programu. Przyjmuje jako argument wskaźnik do
otwartego pliku i wypisuje jego zawartość, działając w pętli while. 

	na początek deklarujemy zmienne przechowujące: aktualny adres odczytu, odczytane bajty
	z pliku oraz ilość tych odczytanych bajtów ("i" to zmienna pomocnicza do pętli);
	
	następnie przy pomocy pętli while najpierw:
		wyświetlamy aktualny adres w postaci heksadecymalnej z wypełnieniem zerami na początku (linijka 31);
		
		potem wykorzystujemy funkcję "print_hex()";
		
		dalej sprawdzamy, czy odczytano mniej bajtów, niż stała	"MAX_LINE_LENGTH" (jeśli tak, to ostatnia linia,
		więc dodajemy wyrównanie spacjami);
		
		później dodajemy dodatkową spację między sekcją szesnastkową a tekstową (linia 42);

		wyświetlamy odczytane bajty z bufora jako tekst funkcją "print_text()"; 
		
		wyświetlamy nową linię po wyświetleniu całej pojedynczej lini heksadecymalnej i tekstowej;
		
		ostatecznie inkrementujemy "adress" o wartość rozmiaru pojedynczej linii;
		
	po wyjściu z pętli wyświetlamy informację o zamykaniu pliku, tak jak w poleceniu.
	
w funkcji "main()" standardowo znajduje się kod wykonywalny. 

	sprawdzamy, czy podano nazwę pliku jako argument wywołania programu. 
	jeśli nie, wypisujemy informację o poprawnym użyciu i kończymy program. 
	w przeciwnym przypadku otwieramy plik do odczytu w trybie binarnym 
	za pomocą "fopen()". Jeśli nie udało się otworzyć pliku, wypisujemy 
	odpowiedni komunikat i kończymy program.
	
	jeśli udało się otworzyć plik, wypisujemy informację o wczytywanym pliku, 
	wywołując funkcję "print_hexdump()" z odpowiednim wskaźnikiem do pliku jako argumentem.
	
	na końcu zamykamy plik za pomocą "fclose()".
*/
