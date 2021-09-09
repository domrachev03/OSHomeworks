#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*
 * The program first prints the ID: it changes from some 
 * value consequently, as we are creating new processes.
 *
 * However, value of variable n in each program is the same,
 * as fork() creates copy of the current program.
 */
int main() {
    int n = 123;

    int x = fork();
    if (x < 0) {
        return EXIT_FAILURE;
    } else if (x == 0) {
        printf("Hello from child %d, n = %d\n", getpid(), n); 
    }else {
        printf("Hello from parent %d, n = %d\n", getpid(), n);
    }
    x = fork();
    
    return EXIT_SUCCESS;
}
