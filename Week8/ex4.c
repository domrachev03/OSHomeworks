#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

#define MByte 1024 * 1024

int main() {
  char **array;
  struct rusage stats;

  array = malloc(10 * sizeof(char *));

  for (int i = 0; i < 10; ++i) {
    array[i] = malloc(1000 * MByte);
    getrusage(RUSAGE_SELF, &stats);
    printf("%ld\n", stats.ru_maxrss);
    array[i] = memset(array[i], 0, 1000 * MByte);

    sleep(1);
  }

  for (int i = 0; i < 10; ++i) {
    free(array[i]);
  }

  free(array);

  return 0;
}
