#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*sprawdzam ilość argumentów programu używając ternary statement*/
bool isSourceFileGiven(int numberOfParameters){
    return numberOfParameters == 2 ? true : false;
}

void printDigitsInReverse(int number){
    /*sprawdzam, czy liczba jest ujemna, jeżeli tak to wyświetlam minus dopiero po wszystkich cyfrach*/
    if(number<0){
        number = abs(number);
        do{
            printf("%d", number%10);
            number = number/10;
        }while(number%10 != 0);
        printf("-");
    }
    else {
        do {
            printf("%d", number % 10);
            number = number / 10;
        } while (number % 10 != 0);
    }
};

int main(int argc, char** argv){
    FILE *fileToRead;
    int numberCount;
    int *numbers;
    int i;

    /*jeżeli nazwa pliku jest podana jako argument*/
    if(isSourceFileGiven(argc)) {
        fileToRead = fopen(argv[1], "r");
        if(fileToRead == NULL) {
            return 0;
        }
        /*pobieram pierwszą linię z liczbą podawanych integerów*/
        fscanf(fileToRead, "%d", &numberCount);
        numbers = malloc(sizeof (int)*numberCount);
        if(numbers == NULL){
            perror("Malloc error: ");
            return -1;
        }
        i = 0;
        /*przypisuje kolejne liczby do tablicy*/
        while(i<numberCount){
            fscanf(fileToRead, "%d", &numbers[i]);
            i++;
        }
    }
    /*w przeciwnym razie pobieramy plik bezpośrednio ze standardowego inputu*/
    else {
        fscanf(stdin, "%d", &numberCount);
        numbers = malloc(sizeof (int)*numberCount);
        if(numbers == NULL){
            perror("Malloc error: ");
            return -1;
        }
        i = 0;
        while(i<numberCount){
            fscanf(stdin, "%d", &numbers[i]);
            i++;
        }
    }
    /*niezależnie od wyniku poprzedniego if'a iteruje przez liczby z talbicy numbers w odwrotnej kolejności*/
    for (i = numberCount-1; i >= 0; i--){
        /*na każdej liczbie używam funkcji, która wyświetla cyfry liczby w odwrotnej kolejności*/
        printDigitsInReverse(numbers[i]);
        if(i != 0){
            printf("\n");
        }
    }
    /*zwalniam przestrzeń adresową zajmowaną przez tablice*/
    free(numbers);
    fclose(fileToRead);
    return 0;
}
