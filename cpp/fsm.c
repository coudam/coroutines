#include <stdio.h>
#include <time.h>

#define start(state)                                                           \
  switch (state) {                                                             \
  case 0:;

#define finish                                                                 \
  default:;                                                                    \
    }

#define yield(state, value)                                                    \
  do {                                                                         \
    state = __LINE__;                                                          \
    return (value);                                                            \
  case __LINE__:;                                                              \
  } while (0)

// FSM:
// A -- 'a' --> B
// A -- 'b' --> C
// B -- 'a' --> C
// B -- 'b' --> A
// C -- 'a' --> A
// C -- 'b' --> B
int run(char input) {
  static int state = 0;
  start(state) {
  A:
    printf("A\n");
    yield(state, 1);
    if (input == 'a')
      goto B;
    if (input == 'b')
      goto C;
  B:
    printf("B\n");
    yield(state, 2);
    if (input == 'a')
      goto C;
    if (input == 'b')
      goto A;
  C:
    printf("C\n");
    yield(state, 3);
    if (input == 'a')
      goto A;
    if (input == 'b')
      goto B;
  }
  finish;

  return 0;
}

int main() {
  int a, s = 0, t;
  clock_t start, fin;
  
  start = clock();  
  while ((a = getchar()) != EOF && (s = run(a)) != 0) {
    t = s;
  }
  fin = clock();

  printf("Elapsed: %lg seconds\n", (double)(fin - start) / CLOCKS_PER_SEC);
  printf("final: %d\n", t);
  return 0;
}
