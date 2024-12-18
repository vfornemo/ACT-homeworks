#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

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
    size_t Natoms = 0;
    int c;
    FILE* input_file = fopen(filename, "r");
    if (!input_file){
        printf("Could not open file\n");
        return (size_t)-1; // Return an invalid value to indicate error
    }

    // Read the number of atoms from the first line
    if (fscanf(input_file, "%zu", &Natoms) != 1) {
        printf("Error reading number of atoms\n");
        fclose(input_file);
        return (size_t)-1; // Return an invalid value to indicate error
    }

    fclose(input_file);
    return Natoms;
}

// Function to read number of atoms, coordinates, and masses
void read_molecule(FILE* input_file, size_t* Natoms, double** coord, double* mass) {
    if (input_file == NULL) {
        printf("Invalid file pointer\n");
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

// Function to evaluate internuclear distances
void compute_distances(size_t Natoms, double** coord, double** distance) {
    for (size_t i = 0; i < Natoms; i++) {
        for (size_t j = 0; j < Natoms; j++) {
            if (i != j) {
                // Evaluates distance between atoms i and j
                double dx = coord[i][0] - coord[j][0];
                double dy = coord[i][1] - coord[j][1];
                double dz = coord[i][2] - coord[j][2];
                distance[i][j] = sqrt(dx*dx + dy*dy + dz*dz);  // 3D Euclidean distance
            } else {
                distance[i][j] = 0.0;  // Distance from one atom to itself
            }
        }
    }
}

int main() {
    size_t Natoms;

    // Read the number of atoms from the file first
    FILE* input_file = fopen("inp.txt", "r");
    if (!input_file) {
        printf("Could not open file: inp.txt\n");
        return 1; // Exit if file can't be opened
    }

    // Read the number of atoms
    Natoms = read_Natoms("inp.txt");  // This should return the number of atoms

    if (Natoms == (size_t)-1) {
        printf("Error reading number of atoms.\n");
        fclose(input_file);
        return 1; // Exit on error
    }

    // Allocate memory for the coordinates (3 values per atom)
    double** coord = malloc_2d(Natoms, 3);  // Allocate memory for Natoms x 3 coordinates

    // Allocate memory for the masses
    double* mass = malloc(Natoms * sizeof(double)); // Allocate memory for Natoms masses

    // Read the molecule data (coordinates and masses)
    read_molecule(input_file, &Natoms, coord, mass);

    // Print the read data to verify
    for (size_t i = 0; i < Natoms; i++) {
        printf("Atom %zu: Coordinates (%.2f, %.2f, %.2f), Mass: %.2f\n",
               i + 1, coord[i][0], coord[i][1], coord[i][2], mass[i]);
    }

    // Allocate memory for the distance array (Natoms x Natoms)
    double** distance = malloc_2d(Natoms, Natoms);

    // Compute the internuclear distances
    compute_distances(Natoms, coord, distance);

    // Print the calculated distances
    for (size_t i = 0; i < Natoms; i++) {
        for (size_t j = 0; j < Natoms; j++) {
            printf("Distance between atom %zu and atom %zu: %f\n", i+1, j+1, distance[i][j]);
        }
    }

    // Free the allocated memory
    free_2d(coord);
    free(mass);
    free_2d(distance);

    fclose(input_file); // Close the file
    return 0;
}
