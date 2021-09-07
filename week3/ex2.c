#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void bubble_sort(int n, int *array) {
	for(int i = 0; i < n; ++i) {
		for(int k = 1; k < n; ++k) {
			if(array[k-1] > array[k]) {
				swap(&array[k-1], &array[k]);
			}
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	int *array = (int*)malloc(n*sizeof(int));
	for (int i = 0; i < n; ++i) {
		scanf("%d", &array[i]);
	}

	bubble_sort(n, array);
	
	for (int i = 0; i < n; ++i) {
		printf("%d, ", array[i]);
	}
	free(array);
	return 0;
}
	
