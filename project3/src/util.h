/**
 * @file util.h
 * @author Lavínia Gabriela Teodoro Dos Santos, Tianyi Gao
 * @brief This module contains the utility functions for memory allocation, reading input files, and writing output files
 * @version 1.0
 * @date 2025-01-10
 * 
 * @copyright GNU Public License V3.0
 * 
 */

#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

/**
 * @brief Function to allocate 2D array mxn
 * 
 * @param m, n dimensions of the 2D array
 * @return double** pointer to the 2D array
 */
double** malloc_2d(size_t m, size_t n);

/**
 * @brief Function to free the memory for 2D arrays after use
 * 
 * @param a pointer to the 2D array
 */
void free_2d(double** a);

/**
 * @brief Function to read the number of atoms from input file
 * 
 * @param filename name of the input file
 * @return size_t number of atoms
 */
size_t read_Natoms(const char* filename);

/**
 * @brief Function to read number of atoms, coordinates, and masses
 * 
 * @param input_file file pointer to the input file
 * @param Natoms number of atoms
 * @param coord pointer to the coordinates 2D array
 * @param mass pointer to the masses array
 */
void read_molecule(FILE* input_file, size_t* Natoms, double** coord, double* mass);

/**
 * @brief Function to evaluate internuclear distances
 * 
 * @param Natoms number of atoms
 * @param coord pointer to the coordinates 2D array
 * @param distance pointer to the distances 2D array
 */
void compute_distances(size_t Natoms, double** coord, double** distance);

/**
 * @brief Function to write the coordinates to an xyz file
 * 
 * @param output_file file pointer to the output file
 * @param Natoms number of atoms
 * @param comment comment line for the xyz file, including cycle number, kinetic energy, potential energy, and total energy
 * @param coord pointer to the coordinates 2D array
 */
void write_xyz(FILE* output_file, size_t Natoms, char* comment, double** coord);

#endif