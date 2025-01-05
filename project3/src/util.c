#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "util.h"

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

    size_t x;
    fscanf(input_file, "%zu", &x);  // Jump over the first line with the number of atoms

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

void write_xyz(FILE* output_file, size_t Natoms, char* comment, double** coord) {
    if (output_file == NULL) {
        printf("Invalid file pointer to write xyz file\n");
        return;
    }

    // Write the number of atoms and a comment line
    fprintf(output_file, "%zu\n%s\n", Natoms, comment);

    // Write the coordinates of each atom
    for (size_t i = 0; i < Natoms; i++) {
        fprintf(output_file, "Ar %.6f %.6f %.6f\n", coord[i][0], coord[i][1], coord[i][2]);
    }

    fprintf(output_file, "\n");  // Add an empty line at the end
}