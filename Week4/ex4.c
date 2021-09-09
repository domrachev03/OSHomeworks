#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char command[500];
    while(1) {
        
        printf(">");
        
        scanf("%[^\n]%*c", command);
        
        char *argv[50];
        int pos = 0;
        argv[pos] = strtok(command, " ");
        
        while(argv[pos] != NULL) {      
            pos++; 
            argv[pos] = strtok(NULL, " ");
        }

        if(!strcmp(argv[0], "exit")) {
            return 0;
        } else {
            int x = fork();

            if (x == 0) {
                execvp(argv[0], argv);
            }
        }
        wait(NULL);
    }

    return 0;
}

