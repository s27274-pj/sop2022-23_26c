#include <stdio.h>
#include <sys/types.h>

pid_t getpid(void);
pid_t getppid(void);

int main() {
    pid_t pid = getpid();		/* Pobranie numeru PID */
    pid_t ppid = getppid();		/* Pobranie numeru PPID */

    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);

    printf("Waiting for user input...\n");

 	/* Oczekiwanie na dane od użytkownika */
    getchar();

    return 0;
}

/*
program jest dość prosty, dlatego poniżej umieszczam krótki opis funkcji 
poznanych na zajęciach, do ew. późniejszego przypomnienia przy nauce:

- fork():

	dunkcja "fork()" tworzy nowy proces przez duplikowanie bieżącego procesu.
	tworzony jest identyczny proces potomny, który wykonuje kod początkowy od momentu 
	wywołania "fork()". Funkcja zwraca wartość 0 dla procesu potomnego i wartość większą 
	niż 0 (identyfikator procesu potomnego) dla procesu macierzystego. Procesy potomne 
	mają unikalne identyfikatory PID (Process ID).

- wait():

	funkcja "wait()" czeka na zakończenie dowolnego procesu potomnego.
	jeśli istnieją aktywne procesy potomne, funkcja zablokuje wykonywanie
	procesu macierzystego do momentu zakończenia któregoś z procesów potomnych.
	funkcja zwraca identyfikator PID zakończonego procesu potomnego.

- waitpid():

	funkcja "waitpid()" czeka na zakończenie określonego procesu potomnego o podanym 
	identyfikatorze PID. Pozwala na bardziej precyzyjne zarządzanie oczekiwaniem 
	na konkretne procesy potomne. 
	
- getpid():

	funkcja "getpid()" zwraca identyfikator PID bieżącego procesu.
	jest przydatna do identyfikacji procesów wewnątrz systemu operacyjnego.
	
- getppid():

	funkcja getppid() zwraca identyfikator PID procesu macierzystego bieżącego procesu.
	umożliwia identyfikację procesu macierzystego wewnątrz systemu operacyjnego.
	
- ps auxf:

	"ps" to polecenie wyświetlające listę procesów aktualnie uruchomionych w systemie, 
	do których użytkownik wykonujący ma dostęp. Przyjmuje różne parametry.
*/
