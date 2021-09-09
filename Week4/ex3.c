#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char command[50];
    while(1) {
        printf(">");
        scanf("%s", command);
        if(!strcmp(command, "exit")) {
            return 0;
        } else {
            system(command);
        }
    }

    return 0;
}

