#include <dirent.h>
#include <stdio.h>

int main() {
  DIR *dir;
  dir = opendir("/");

  struct dirent *dir_info = readdir(dir);

  while (dir_info != NULL) {
    printf("%s\n", dir_info->d_name);
    dir_info = readdir(dir);
  }

  return 0;
}
