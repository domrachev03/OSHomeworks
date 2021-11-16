#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool char
#define true (1)
#define false (0)

/*
 * This program automatically finds the amount of processes and
 * amount of resourses. However, the format of the input data have to be
 * the same as in the example:
 * 7 2 6
 *
 * 0 0 0
 *
 * 0 1 0
 * 2 0 0
 * 3 0 3
 * 2 1 1
 * 0 0 2
 *
 *
 * 0 0 0
 * 2 0 2
 * 0 0 0
 * 1 0 0
 * 0 0 2
 *
 * Notice, that there are two empty lines between matrices
 */

int main() {
  int nprocs = 0, nres = 0;

  char *input_line = malloc(255 * sizeof(char));
  FILE *f = fopen("input.txt", "r");

  int *e = malloc(255 * sizeof(int));

  fgets(input_line, 255, f);

  char *cur_token = strtok(input_line, " ");

  while (cur_token != NULL) {
    e[nres++] = atoi(cur_token);
    cur_token = strtok(NULL, " ");
  }
  e = realloc(e, nres * sizeof(int));
  if (e == NULL) {
    printf("Bruh");
  }
  fgets(input_line, 255, f);
  fgets(input_line, 255, f);

  int *a = malloc(nres * sizeof(int));
  int i = 0;

  cur_token = strtok(input_line, " ");

  while (cur_token != NULL) {
    a[i++] = atoi(cur_token);
    cur_token = strtok(NULL, " ");
  }

  fgets(input_line, 255, f);
  fgets(input_line, 255, f);
  int **c = malloc(255 * sizeof(int *));

  while (strcmp(input_line, "\n")) {
    c[nprocs] = malloc(nres * sizeof(int));

    cur_token = strtok(input_line, " ");
    int k = 0;
    while (cur_token != NULL) {
      c[nprocs][k++] = atoi(cur_token);
      cur_token = strtok(NULL, " ");
    }

    nprocs++;
    fgets(input_line, 255, f);
  }

  c = realloc(c, nprocs * sizeof(int *));

  fgets(input_line, 255, f);

  int **r = malloc(nprocs * sizeof(int *));
  int j = 0;
  while (fgets(input_line, 255, f)) {
    r[j] = malloc(nres * sizeof(int));

    cur_token = strtok(input_line, " ");
    int k = 0;
    while (cur_token != NULL) {
      r[j][k++] = atoi(cur_token);
      cur_token = strtok(NULL, " ");
    }

    ++j;
  }
  fclose(f);
  free(cur_token);
  free(input_line);

  printf("\nE:\n");
  for (int i = 0; i < nres; ++i) {
    printf("%d ", e[i]);
  }
  printf("\n\nA:\n");

  for (int i = 0; i < nres; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n\nC:\n");

  for (int i = 0; i < nprocs; ++i) {
    for (int k = 0; k < nres; ++k) {
      printf("%d ", c[i][k]);
    }
    printf("\n");
  }
  printf("\nR:\n");
  for (int i = 0; i < nprocs; ++i) {
    for (int k = 0; k < nres; ++k) {
      printf("%d ", r[i][k]);
    }
    printf("\n");
  }
  printf("\nCheck for deadlocks\n--------------------------------------\n");
  bool wasChanged = true;
  bool *process_executed = malloc(nprocs * sizeof(bool));

  for (int i = 0; i < nprocs; ++i) {
    process_executed[i] = false;
  }

  while (wasChanged) {
    wasChanged = false;

    for (int cur_proc = 0; cur_proc != nprocs; ++cur_proc) {
      if (process_executed[cur_proc])
        continue;

      bool process_executable = true;
      for (int cur_res = 0; cur_res != nres; ++cur_res) {
        if (a[cur_res] + c[cur_proc][cur_res] < r[cur_proc][cur_res]) {
          process_executable = false;
          break;
        }
      }

      if (process_executable) {
        wasChanged = true;

        for (int cur_res = 0; cur_res != nres; ++cur_res) {
          a[cur_res] += c[cur_proc][cur_res];
        }

        process_executed[cur_proc] = true;
      }
    }

    printf("List of executed processes:\n");
    for (int i = 0; i != nprocs; ++i) {
      if (process_executed[i]) {
        printf("Yes ");
      } else {
        printf("No ");
      }
    }
    printf("\nCurrent availvable resourses:\n");
    for (int i = 0; i != nres; ++i) {
      printf("%d ", a[i]);
    }
    printf("\n--------------------------------------\n");
  }

  int ndeadlocks = 0;

  for (int i = 0; i < nprocs; ++i) {
    if (!process_executed[i]) {
      ++ndeadlocks;
    }
  }

  if (!ndeadlocks) {
    printf("No deadlocks found!\n");
  } else {
    printf("There are %d deadlocked processes :(\n", ndeadlocks);
  }

  return 0;
}
