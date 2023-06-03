#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void abort(void) {
  fprintf(stderr, "Błąd odczytu\n");
  exit(1);
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a > b ? b : a; }
int sum(int a, int b) { return a + b; }

typedef int (*fun)(int, int);

int forAll(int *arr, size_t len, fun f) {
  size_t i;
  int acc;

  acc = arr[0];
  for (i = 1; i < len; i += 1)
    acc = f(acc, arr[i]);

  return acc;
}

int main() {
  fun funs[3] = {max, min, sum};
  uint8_t functionId;
  size_t elementCount, i;
  int *arr, v;

  if (scanf("%" PRIu8 " %zu", &functionId, &elementCount) != 2 ||
      functionId > 2)
    abort();

  arr = calloc(elementCount, sizeof(int));
  if (!arr) {
    fprintf(stderr, "Błąd alokacji\n");
    return 1;
  }
  for (i = 0; i < elementCount; i += 1)
    if (scanf("%d", &arr[i]) != 1)
      abort();

  /*
  v = arr[0];
  for (i = 1; i < elementCount; i += 1)
    v = (funs[functionId])(v, arr[i]);
  */
  v = forAll(arr, elementCount, funs[functionId]);

  printf("%d\n", v);

  free(arr);
  return 0;
}
