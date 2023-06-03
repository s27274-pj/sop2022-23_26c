/* clang-format off */
/*------------------------------------------------------------------------------------------*\
 |                                                                                          |
 | Napisz program, który wygeneruje drzewko procesów wyglądające tak                        |
 | (oczywiście procesy nie będą się nazywały A, B, ...):                                    |
 |                                                                                          |
 | A \                                                                                      |
 |   |\B \                                                                                  |
 |   |   |\D                                                                                |
 |   |    \E                                                                                |
 |    \C \                                                                                  |
 |       |\F                                                                                |
 |        \G                                                                                |
 |                                                                                          |
 | A jest rodzicem 2 procesów - B oraz C, a te są odpowiednio rodzicami D i E, oraz F i G.  |
 |                                                                                          |
\*------------------------------------------------------------------------------------------*/
/* clang-format on */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int depth = 0, spawned_children = 0;

  while (depth < 2 && spawned_children < 2) {
    switch (fork()) {
    case -1:
      fprintf(stderr, "Fork nie powiódł się\n");
      return 1;
    case 0:
      spawned_children = 0;
      depth += 1;
      break;
    default:
      spawned_children += 1;
    }
  }

  while (1)
    pause();

  return 0;
}
