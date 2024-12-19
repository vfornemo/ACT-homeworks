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


