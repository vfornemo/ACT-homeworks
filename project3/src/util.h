#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

// Function to allocate 2D array mxn
double** malloc_2d(size_t m, size_t n);

// Function to free the memory for 2D arrays after use
void free_2d(double** a);

// Function to read the number of atoms from input file inp.txt
size_t read_Natoms(const char* filename);

// Function to read number of atoms, coordinates, and masses
void read_molecule(FILE* input_file, size_t* Natoms, double** coord, double* mass);

// Function to evaluate internuclear distances
void compute_distances(size_t Natoms, double** coord, double** distance);

void write_xyz(FILE* output_file, size_t Natoms, char* comment, double** coord);

#endif