/**
 * @file main.c
 * @author Lavínia Gabriela Teodoro Dos Santos, Yifan Jiang, Tianyi Gao

 * @brief This program reads from the input file and performs molecular dynamics simulation
 * @version 1.0
 * @date 2025-01-10
 * 
 * @copyright GNU Public License V3.0
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "energy.h"

//! Application entry
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

    int step = 1000;
    double dt = 0.2;

    double** velocity = malloc_2d(Natoms, 3);
    for (size_t i = 0; i < Natoms; i++) {
        for (size_t j = 0; j < 3; j++) {
            velocity[i][j] = 0.0;
        }
    }
    double** acceleration = malloc_2d(Natoms, 3);
    compute_acc(Natoms, coord, mass, distance, acceleration);

    int cycle = 0;
    FILE* out = fopen("output.xyz", "w");

    while (cycle < step) {
        for (size_t i = 0; i < Natoms; i++) {
            for (size_t j = 0; j < 3; j++) {
                // compute r(n+1) and v(n+1)
                coord[i][j] += velocity[i][j] * dt + 0.5 * acceleration[i][j] * dt * dt;
                velocity[i][j] += 0.5 * acceleration[i][j] * dt;
            }
        }

        // compute a(n+1)
        compute_acc(Natoms, coord, mass, distance, acceleration);

        for (size_t i = 0; i < Natoms; i++) {
            for (size_t j = 0; j < 3; j++) {
                // finalize v(n+1)
                velocity[i][j] += 0.5 * acceleration[i][j] * dt;
            }
        }

        compute_distances(Natoms, coord, distance); // TODO: make sure the distance needs to be updated

        cycle++;

        if (cycle % 10 == 0) {
            // printf("Number of atoms: %zu\n", Natoms);
            // printf("Kinetic energy: %f ", T(Natoms, velocity, mass));
            // printf("Potential energy: %f ", V(EPSILON, SIGMA, Natoms, distance));
            // printf("Total energy: %f\n", E(Natoms, velocity, mass, EPSILON, SIGMA, distance));
            // format comment
            char* comment = malloc(100 * sizeof(char));
            sprintf(comment, "Cycle=%d, T=%.6f, V=%.6f, E=%.6f",cycle, T(Natoms, velocity, mass), V(EPSILON, SIGMA, Natoms, distance), E(Natoms, velocity, mass, EPSILON, SIGMA, distance));
            write_xyz(out, Natoms, comment, coord);
            // TODO: check if the total energy is conserved
        }
    }

    fclose(out);  // Close the output file

    // Free the allocated memory
    free_2d(coord);
    free(mass);
    free_2d(distance);
    free_2d(velocity);
    free_2d(acceleration);

    fclose(input_file); // Close the file
    return 0;
}
