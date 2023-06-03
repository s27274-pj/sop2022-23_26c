#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    int (*functions[3])(int, int) = {max, min, sum};
    int functionId, elementCount, x, i, z;
    
    scanf("%d%d%d", &functionId, &elementCount, &x);
    
    for (i = 1; i < elementCount; ++i) {
        scanf("%d", &z);
        x = (*functions[functionId])(x, z);
    }
    
    printf("%d\n", x);
    
    return 0;
}
