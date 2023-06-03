#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int i;
    printf("Moj PID to: %d\n", getpid());
    scanf("%d", &i); /* teraz KILL -9 PID */
    return 0;
}
