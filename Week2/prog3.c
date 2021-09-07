#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{	
	int n;
	if(argc > 1) {
		sscanf(argv[1], "%d", &n);
	}
	for(int i = 0; i < n; ++i) {
		for(int k = 0; k < n-i; ++k) {
			printf(" ");
		}
		for(int k = 0; k < 2*i + 1; ++k) {
			printf("*");
		}
		printf("\n");
	}
	return EXIT_SUCCESS;
}
