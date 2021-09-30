#include <stdio.h>
#include <stdlib.h>

int main() {
  // char **s; - we do not allocate memory for pointer
  char **s = malloc(sizeof(char *));
  char foo[] = "Hello World";
  *s = foo;

  printf("s is %s\n", *s);
  s[0] = foo; // This line probably produces not expected result, however it
              // doesn't produce segfault (at least on gcc compiler)
  printf("S[0] is %s\n", s[0]);

  return 0;
}
