#include <fcntl.h>
#include <inttypes.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  struct input_event event;
  char input_file[] = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
  int key = open(input_file, O_RDONLY);
  FILE *f = fopen("ex2.txt", "w");

  if (key < 0) {
    printf("Fail!");
    return 1;
  }

  while (1) {
    read(key, &event, sizeof(struct input_event));

    if (event.type != 1)
      continue;

    if (event.value == 1) {
      printf("PRESSED 0X%X (%d)\n", event.code, event.code);
    } else if (event.value == 0) {
      printf("RELEASED 0X%X (%d)\n", event.code, event.code);
    }

    fflush(stdout);
  }

  return 0;
}
