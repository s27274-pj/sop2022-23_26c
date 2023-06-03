#include <stdio.h>

int fib_recur(int n) { return n > 1 ? fib_recur(n - 1) + fib_recur(n - 2) : n; }

int fib_iter(int n) {
  int a = 0, b = 1, tmp, sum = 1;

  if (!n)
    return 0;

  for (; n > 1; n -= 1) {
    sum = a + b;
    tmp = b;
    b += a;
    a = tmp;
  }

  return sum;
}

int main() {
  printf("%d\n", fib_recur(34));
  printf("%d\n", fib_iter(34));
  return 0;
}
