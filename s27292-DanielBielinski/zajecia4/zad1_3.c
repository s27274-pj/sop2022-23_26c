#include<stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int rozmiar = atoi(argv[1]);
    int i,j;
    for(i = 0 ; i < rozmiar ; i++ ){
        for(j = 0 ; j < rozmiar -  i ; j++) putchar(' ');
        for (j = 0 ; j < i*2+1 ; j++) putchar('*');
        putchar('\n');
    }
    for(i = 0 ; i < rozmiar*2 ; i++){
        if(i==rozmiar){
            putchar('*');
        } else {
            putchar(' ');
        }
    }
    putchar('\n');
    return 0;
}
