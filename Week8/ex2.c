#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MByte 1024 * 1024

/* After starting several instances of this program in the background
 * my computer started to make lots of swap out operations, as all 16 GB
 * of RAM ended. You can consider report at the file ex2.txt
 *
 * Calling top command verified results: PC ran out of memory and started
 * using all swap memory it could. However, it was still not enough, so some
 * programs crashed (and also all instances of program were killed)*/
int main() {
  char **array;

  array = malloc(10 * sizeof(char *));

  for (int i = 0; i < 10; ++i) {
    array[i] = malloc(1000 * MByte);
    array[i] = memset(array[i], 0, 1000 * MByte);

    sleep(1);
  }

  for (int i = 0; i < 10; ++i) {
    free(array[i]);
  }

  free(array);

  return 0;
}
