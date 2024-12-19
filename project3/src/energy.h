#ifndef ENERGY_H
#define ENERGY_H

#include <stddef.h>
#include <math.h>

/// @brief compute L-J potential
/// @param epsilon L-J coefficient
/// @param sigma L-J coefficient
/// @param Natoms number of atoms
/// @param distance distances between atoms
/// @return potiential energy
double V(double epsilon, double sigma, size_t Natoms, double** distance);

/// @brief compute kinetic energy
/// @param Natoms number of atoms
/// @param velocity velocities of atoms
/// @param mass mass of atoms
/// @return kinetic energy
double T(size_t Natoms, double** velocity, double* mass);

/// @brief compute total energy
/// @param Natoms number of atoms
/// @param velocity velocities of atoms
/// @param mass mass of atoms
/// @param epsilon L-J coefficient
/// @param sigma L-J coefficient
/// @param distance distances between atoms
/// @return total energy
inline double E(size_t Natoms, double** velocity, double* mass, double epsilon, double sigma, double ** distance) {
    return V(epsilon, sigma, Natoms, distance) + T(Natoms, velocity, mass);
}

inline double U(double epsilon, double sigma, double r) {
    return 24 * epsilon / r *(pow(sigma / r, 6.0) - 2 * pow(sigma / r, 12.0));
}


#endif