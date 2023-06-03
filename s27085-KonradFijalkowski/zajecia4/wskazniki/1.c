#include <stdio.h>
#include <stdlib.h>
int min(int a, int b);
int max(int a, int b);
int sum(int a, int b);
typedef int (*operation)(int,int);

int main(int argc, char ** argv){
    operation funcPointers[] = {min, max, sum};
    unsigned int functionId = atoi(argv[1]);
    unsigned int elementCount = atoi(argv[2]);
    int v = atoi (argv[3]);
    int i;

    if(argc < 4 || argc != atoi(argv[2])+3){
        printf("Invalid number of parameters given");
        exit(EXIT_FAILURE);
    }
    /*iteruje się za każdym razem używają wskazanej funkcji na zmiennej v i kolejnym argumencie programu*/
    for(i = 0; i < elementCount-1; i++) {
        v = funcPointers[functionId](v, atoi(argv[4+i]));
    }
    printf("V equals %d\n", v);
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
