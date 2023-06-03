#include <stdio.h>

int maksimum(int a, int b){ return a > b ? a : b ; }
int minimum(int a, int b){ return a < b ? a : b ; }
int suma(int a, int b){ return a + b ; }

int main(){
    int (*funkcje[3])(int,int) = {maksimum,minimum,suma};
    int functionId,elementCount,*elementNumber,v,i;
    scanf("%d %d",&functionId,&elementCount);
    for(i = 0 ; i < elementCount ; i++){
        scanf("%d",&elementNumber[i]);
    }
    v = elementNumber[0];
    for (i = 1; i < elementCount; i++){
        v = funkcje[functionId](v,elementNumber[i]);
    }
    printf("%d\n",v);
    return 0;
}
