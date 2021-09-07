#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <float.h>

int main(void)
{
	int a = INT_MAX;
	double b = DBL_MAX;
	float c = FLT_MAX;
	printf("%d %d %d\n", sizeof(a), sizeof(b), sizeof(c));
	printf("Int max: %d\nFloat max:%f\nDouble max:%lf\n", a, b, c);
	return EXIT_SUCCESS;
}
