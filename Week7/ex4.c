#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void *my_realloc(void *ptr, size_t new_size) {
  if (!ptr) {
    return malloc(new_size);
  }

  void *new_ptr = malloc(new_size);

  memcpy(new_ptr, ptr, new_size);
  free(ptr);
  return new_ptr;
}

#define N 5

int main() {
  int *array = 0;
  array = my_realloc(array, N * sizeof(int));

  for (int i = 0; i < N; ++i) {
    array[i] = i;
    printf("%d ", array[i]);
  }

  printf("\n");

  array = my_realloc(array, 2 * N * sizeof(int));
  for (int i = N; i < 2 * N; ++i) {
    array[i] = i;
  }

  printf("\n");

  for (int i = 0; i < 2 * N; ++i) {
    printf("%d ", array[i]);
  }

  printf("\n");

  array = my_realloc(array, sizeof(int));

  printf("%d", array[0]);

  return 0;
}
