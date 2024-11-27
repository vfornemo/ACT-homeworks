#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// Function to allocate 2D array mxn
double** malloc_2d(size_t m, size_t n) {
	// Array of double pointers with size m
	double** a = malloc(m*sizeof(double*));
	if (a == NULL) {
	return NULL;
	}

	// Allocate a contiguous block of memory for the 2D array elements
	a[0] = malloc(n*m*sizeof(double));
	if (a[0] == NULL) {
	free(a);
	return NULL;
	}
	/* Set the pointers in the array of double pointers
	to point to the correct locations*/
	for (size_t i=1 ; i<m ; i++) {
	a[i] = a[i-1]+n;
	}
	if (a != NULL){
		printf("\n2D Allocation OK!\n");
	}
	return a;
}

// Function to free the memory for 2D arrays after use
void free_2d(double** a) {
	free(a[0]);
	a[0] = NULL;
	free(a);
}

int main() {
	double** a1=malloc_2d(3,4);
	printf("\n%p\n",&a1);
	free_2d(a1);
}
