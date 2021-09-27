#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int a = INT_MAX;
  double b = DBL_MX;
  float c = FLT_MAX;
  printf("%d %d %d\n", sizeof(a), sizeof(b), sizeof(c));
  printf("Int max: %d\nFloat max:%f\nDouble max:%lf\n", a, b, c);
  return EXIT_SUCCESS;
}
