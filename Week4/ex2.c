#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * As a result of looking on process tree, 
 * we would see a process tree, which will
 * illustrate all processes we created. 
 */
int main() {
    for(int i = 0; i < 3; ++i) {
        fork();
        sleep(5);
    }
    return 0;
}
