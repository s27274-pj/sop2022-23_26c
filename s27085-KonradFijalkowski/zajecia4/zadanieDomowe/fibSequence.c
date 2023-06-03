#include <stdio.h>
#include <stdlib.h>

int fibRec(int soughtElement){
    if(soughtElement == 0){
        return 0;
    }
    if(soughtElement == 1){
        return 1;
    }
    return fibRec(soughtElement-1) + fibRec(soughtElement-2);
}

int fibIter(int soughtElement){
    int augend = 0, addend = 1, sum, i;
    if(soughtElement == 0){
        return 0;
    }
    if(soughtElement == 1){
        return 1;
    }
    for(i = 2; i <= soughtElement; i++){
        sum = augend + addend;
        augend = addend;
        addend = sum;
    }
    return sum;
}

int main(int argc, char ** argv){
    int fibNumber;
    if(argc != 2){
        printf("Provide number of Fibonacci sequence element.");
        exit(EXIT_FAILURE);

    }
    fibNumber = atoi(argv[1]);
    if(fibNumber < 0){
        printf("Number must be natural or zero.");
        exit(EXIT_FAILURE);
    }
    printf("fibonacci sequence recursively: %d\n", fibIter(fibNumber));
    printf("fibonacci sequence iteratively: %d\n", fibIter(fibNumber));

    return 0;
}
