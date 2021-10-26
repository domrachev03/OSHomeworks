#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define bool unsigned char
#define true 1
#define false 0

int MAX_FILES = 100;

struct multipointed {
  int st_ino;
  int st_nlink;
  char **file_names;
  int cur_files_found;
};

char *absolute_path(char *name, char *directory) {
  printf("Name: %s, Directory: %s\n", name, directory);

  if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
    return NULL;
  }

  char *full_name = (char *)malloc(1000 * sizeof(char));

  strcpy(full_name, directory);
  strcat(full_name, "/");
  strcat(full_name, name);

  char buff[PATH_MAX + 1];
  char *absolute_path = realpath(full_name, buff);

  free(full_name);
  return absolute_path;
}

int main() {
  char *name = "tmp";
  DIR *dirp = opendir(name);

  if (dirp == NULL) {
    printf("Directory error!");
    return 0;
  }

  struct dirent *cur_file;
  struct stat *cur_stat;
  struct multipointed *duplicates =
      (struct multipointed *)malloc(MAX_FILES * sizeof(struct multipointed));

  int nduplicates = 0;

  while ((cur_file = readdir(dirp)) != NULL) {
    // printf("%s\n", cur_file->d_name);

    char *path = absolute_path(cur_file->d_name, name);

    if (path == NULL) {
      continue;
    }

    stat(path, cur_stat);

    if (cur_stat->st_nlink != 1) {
      bool flag = false;

      for (int i = 0; i < nduplicates; ++i) {
        if (duplicates[i].st_ino == cur_stat->st_ino) {
          duplicates[i].file_names[duplicates[i].cur_files_found] =
              cur_file->d_name;

          duplicates[i].cur_files_found++;
          flag = true;
          break;
        }
      }

      if (flag == false) {
        struct multipointed new_dupl;

        new_dupl.st_ino = cur_stat->st_ino;
        new_dupl.st_nlink = cur_stat->st_nlink;
        new_dupl.file_names =
            (char **)malloc(new_dupl.st_nlink * sizeof(char *));
        new_dupl.file_names[0] = cur_file->d_name;
        new_dupl.cur_files_found = 1;

        duplicates[nduplicates] = new_dupl;
        nduplicates++;
      }
    }
  }

  printf("File ----------------- Hard Links\n");

  for (int i = 0; i < nduplicates; ++i) {
    for (int k = 0; k < duplicates[i].cur_files_found; ++k) {
      printf("%s ----------------- ", duplicates[i].file_names[k]);
      for (int j = 0; j < duplicates[i].cur_files_found; ++j) {
        printf("%s ", duplicates[i].file_names[j]);
      }
    }
    printf("\n");
  }
  return 0;
}
