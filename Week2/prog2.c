#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[256];
	scanf("%s", str);
	int len = strlen(str);
	for(int i = len-1; i >= 0; --i) {
		printf("%c", str[i]);
	}
	return EXIT_SUCCESS; 
}
