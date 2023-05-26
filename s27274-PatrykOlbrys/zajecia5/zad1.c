#include <stdio.h>
/* ^ Nagłówek wymagany do wejścia/wyjścia */

#include <sys/types.h>
#include <unistd.h>
/* ^ Dwa nagłówki wymagane do getpid() i getppid()*/

int main() {
    int data;
    pid_t pid = getpid();
    pid_t ppid = getppid();
    /* ^ Pobieramy pid i ppid 
    Są to zmienne typu pid_t */

    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);
    /* ^ Wyświetlamy je */

    scanf("%d", &data);
    /* ^ Po wypisaniu czekamy
    na dane od użytkownika */

    return 0;
}
