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

// Function to read the number of atoms from input file inp.txt
size_t read_Natoms(const char* filename){
	int c;
        FILE* input_file = fopen(filename,"r");
        if (!input_file){
                printf("Could not open file");
                return -1;
        }
	if (input_file){
		while ((c = getc(input_file))!= EOF)
			putchar(c);
		fclose(input_file);
	}
	return 1;
}

// Function to read number of atoms, coordinates and masses
void readmolecule(FILE* input_file, size_t* Natoms, double** coord, double* mass) {
    if (input_file == NULL) {
        printf("Invalid file pointer\n");
        return;
    }

    // Read the number of atoms from the first line
    if (fscanf(input_file, "%zu", Natoms) != 1) {
        printf("Error reading number of atoms\n");
        return;
    }

    // Read the coordinates and masses from the file
    for (size_t i = 0; i < *Natoms; i++) {
        if (fscanf(input_file, "%lf %lf %lf %lf", &coord[i][0], &coord[i][1], &coord[i][2], &mass[i]) != 4) {
            printf("Error reading data for atom %zu\n", i + 1);
            return;
        }
    }
}


/*int main() {
	double** a1=malloc_2d(3,4);
	printf("\n%p\n",&a1);
	free_2d(a1);
	size_t success = read_Natoms("inp.txt");
	if (success == -1){
		printf("Error reading file. \n");
	}
}*/
int main() {
    size_t Natoms;
    
    // Example: Allocate memory for 4 values (3 coordinates + 1 mass)
    double** a1 = malloc_2d(3, 4); // Assume maximum of 3 atoms (you can adjust based on Natoms)
    printf("\n%p\n", &a1);
    
    double* mass = malloc(3 * sizeof(double)); // Allocate memory for 3 masses (adjust as needed)

    const char* filename = "inp.txt";
    FILE* input_file = fopen(filename, "r");
    if (!input_file) {
        printf("Could not open file: %s\n", filename);
        return 1; // Exit if file can't be opened
    }

    // Read the number of atoms, coordinates, and masses
    readmolecule(input_file, &Natoms, a1, mass);

    // Print the read data to verify
    for (size_t i = 0; i < Natoms; i++) {
        printf("Atom %zu: Coordinates (%.2f, %.2f, %.2f), Mass: %.2f\n",
               i + 1, a1[i][0], a1[i][1], a1[i][2], mass[i]);
    }

    // Free the allocated memory
    free_2d(a1);
    free(mass);

    fclose(input_file); // Close the file
    return 0;
}
