#include "energy.h"
#include <math.h>


double V(double epsilon, double sigma, size_t Natoms, double** distance) {
    double sigma6 = pow(sigma, 6.0);
    double coeff = 4 * epsilon * sigma6;
    double pot = 0.0;
    for (size_t i = 0; i < Natoms; ++i) {
        for (size_t j = i + 1; j < Natoms; ++j) {
            pot += coeff * (sigma6 / pow(distance[i][j], 12.0) - 1.0 / pow(distance[i][j], 6.0));
        }
    }
    return pot;
}


double T(size_t Natoms, double** velocity, double* mass) {
    double kin = 0.0;
    for (size_t i = 0; i < Natoms; ++i) {
        kin += mass[i] + (pow(velocity[i][0], 2) + pow(velocity[i][1], 2) + pow(velocity[i][2], 2));
    }
    return 0.5 * kin;
}

void compute_acc(size_t Natoms, double** coord, double* mass, double** distance, double** acceleration) {
    for (size_t i = 0; i < Natoms; i++) {
        acceleration[i][0] = 0.0;
        acceleration[i][1] = 0.0;
        acceleration[i][2] = 0.0;
        for (size_t j = 0; j < Natoms; j++) {
            if (i != j) {
                double r = distance[i][j];
                double force = U(EPSILON, SIGMA, r) / mass[j];
                acceleration[i][0] -= force * (coord[i][0] - coord[j][0]) / r;
                acceleration[i][1] -= force * (coord[i][1] - coord[j][1]) / r;
                acceleration[i][2] -= force * (coord[i][2] - coord[j][2]) / r;
            }
        }
    }
}

double E(size_t Natoms, double** velocity, double* mass, double epsilon, double sigma, double ** distance) {
    return V(epsilon, sigma, Natoms, distance) + T(Natoms, velocity, mass);
}

double U(double epsilon, double sigma, double r) {
    return 24 * epsilon / r *(pow(sigma / r, 6.0) - 2 * pow(sigma / r, 12.0));
}