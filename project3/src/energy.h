/**
 * @file energy.h
 * @author Yifan Jiang, Tianyi Gao
 * @brief This module contains the functions for energy V, T, E, U as well as acceleration
 * @version 1.0
 * @date 2025-01-10
 * 
 * @copyright GNU Public License V3.0
 * 
 */

#ifndef ENERGY_H
#define ENERGY_H
#define EPSILON 0.0661
#define SIGMA 0.3345

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

/**
 * @brief compute acceleration
 * @param Natoms number of atoms
 * @param coord coordinates of atoms
 * @param mass mass of atoms
 * @param distance distances between atoms
 * @param acceleration acceleration of atoms
 */
void compute_acc(size_t Natoms, double** coord, double* mass, double** distance, double** acceleration);

/// @brief compute total energy
/// @param Natoms number of atoms
/// @param velocity velocities of atoms
/// @param mass mass of atoms
/// @param epsilon L-J coefficient
/// @param sigma L-J coefficient
/// @param distance distances between atoms
/// @return total energy
double E(size_t Natoms, double** velocity, double* mass, double epsilon, double sigma, double ** distance);

/**
 * @brief compute acceleration intermediate U
 * @param epsilon L-J coefficient
 * @param sigma L-J coefficient
 * @param r distance between atoms
 * @return acceleration intermediate U
 */
double U(double epsilon, double sigma, double r);


#endif