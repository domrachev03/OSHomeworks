#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  DIR *dirp = opendir("./tmp");
  if (dirp == NULL) {
    return 0;
  }

  while ((dp = readdir(dirp)))
}
