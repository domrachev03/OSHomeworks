#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MB (1024 * 1024)

int main(int argc, char const *argv[]) {
  size_t i = 0;
  for (i = 0; i < 10; ++i) {
    void *mem = malloc(MB * 10);
    memset(mem, 0, MB * 10);
    sleep(1);
  }
  return 0;
}
