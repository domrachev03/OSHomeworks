#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define INT_TO_VOID(i) (void *)(uintptr_t)(i)

void *func(void *number) {
  printf("Hello from thread %d\n", (int)number);
  return NULL;
}

int main() {
  pthread_t *threads;

  threads = malloc(sizeof(pthread_t) * N);

  for (int i = 0; i < N; ++i) {
    pthread_create(threads + i, NULL, func, INT_TO_VOID(i));
    pthread_join(threads[i], NULL);
  }
  return 0;
}
