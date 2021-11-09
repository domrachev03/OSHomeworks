#include <fcntl.h>
#include <inttypes.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define bool char
#define true 1
#define false 0
#define SHORTKEYS_COUNT 3

struct Shortcut {
  char *msg;
  char *shortcut_name;
  unsigned int *keys;
  unsigned int hotkey_len;
};

int main() {
  struct Shortcut shortcuts[SHORTKEYS_COUNT];

  shortcuts[0].msg = "I passed the exam!";
  shortcuts[0].hotkey_len = 2;
  shortcuts[0].keys = malloc(2 * sizeof(unsigned int));
  shortcuts[0].keys[0] = 25;
  shortcuts[0].keys[1] = 46;
  shortcuts[0].shortcut_name = "P + C";

  shortcuts[1].msg = "Get some cappucino!";
  shortcuts[1].hotkey_len = 3;
  shortcuts[1].keys = malloc(3 * sizeof(unsigned int));
  shortcuts[1].keys[0] = 46;
  shortcuts[1].keys[1] = 30;
  shortcuts[1].keys[2] = 25;
  shortcuts[1].shortcut_name = "C + A + P";

  shortcuts[2].msg = "Press F to pay respect!";
  shortcuts[2].hotkey_len = 2;
  shortcuts[2].keys = malloc(2 * sizeof(unsigned int));
  shortcuts[2].keys[0] = 25;
  shortcuts[2].keys[1] = 33;
  shortcuts[2].shortcut_name = "P + F";

  for (int i = 0; i < SHORTKEYS_COUNT; ++i) {
    printf("Press %s to get message \"%s\"\n", shortcuts[i].shortcut_name,
           shortcuts[i].msg);
  }

  struct input_event event;
  char input_file[] = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
  int key = open(input_file, O_RDONLY);
  FILE *f = fopen("ex2.txt", "w");

  unsigned int *cur_shortcut = malloc(6 * sizeof(unsigned int));
  unsigned int cur_shortcut_len = 0;

  if (key < 0) {
    printf("Fail!");
    return 1;
  }

  while (1) {
    read(key, &event, sizeof(struct input_event));

    if (event.type != 1)
      continue;

    if (event.value == 1) {
      cur_shortcut[cur_shortcut_len++] = event.code;

      for (int i = 0; i < SHORTKEYS_COUNT; ++i) {
        if (shortcuts[i].hotkey_len == cur_shortcut_len) {
          bool if_hotkeys_equal = true;

          for (int k = 0; k < cur_shortcut_len; ++k) {
            if (shortcuts[i].keys[k] != cur_shortcut[k]) {
              if_hotkeys_equal = false;
              break;
            }
          }

          if (if_hotkeys_equal) {
            printf("%s\n", shortcuts[i].msg);
          }
        }
      }
    } else if (event.value == 0) {
      free(cur_shortcut);
      cur_shortcut = malloc(6 * sizeof(unsigned int));

      cur_shortcut_len = 0;
    }

    fflush(stdout);
  }
  return 0;
}
