#include <stdio.h>
#include <stdlib.h>
int min(int a, int b);
int max(int a, int b);
int sum(int a, int b);
typedef int (*operation)(int,int);

int forAll(int * array, unsigned int elemCount, operation pickedOp);

int main(int argc, char ** argv){
    int i;
    int *arguments;
    unsigned int functionId;
    unsigned int elementCount;
    /*tablica przechowująca wskaźniki do funkcji*/
    operation funcPointers[3] = {min, max, sum};
    /*weryfikuje wprowadzone dane czy zgadza się ich ilość*/
    if(argc < 4 || argc != atoi(argv[2])+3){
        printf("Invalid number of parameters given");
        exit(EXIT_FAILURE);
    }
    functionId = atoi(argv[1]);
    elementCount = atoi(argv[2]);
    /*alokuje tablice dla argumentow programu*/
    arguments = malloc(elementCount*sizeof (int));
    if(arguments == NULL){
        perror("Malloc error: ");
        return -1;
    }
    /*wczytuje dane do tabeli*/
    for(i = 0; i < elementCount; i++) {
        arguments[i] =  atoi(argv[3+i]);
    }

    /*wyświetlam wynik dla funkcji, która przyjmuje tabele z argumentami, ich ilość oraz wskaźnik do funkcji*/
    printf("%d", forAll(arguments, elementCount, funcPointers[functionId]));
    free(arguments);
    return 0;
}

int min(int a, int b){
    return (a > b) ? b : a;
}
int max(int a, int b){
    return (a > b) ? a : b;
}
int sum(int a, int b){
    return a + b;
}
int forAll(int * array, unsigned int elemCount, operation pickedOp){
    int result = array[0];
    int i;
    /*przeiteruj tablicę używając na każdym elemencie wybranej funkcji*/
    for(i = 1; i<elemCount; i++){
        result = pickedOp(result, array[i]);
    }
    return result;
}
