#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"

int main() {
    // read data from file
    // open file
    trexio_exit_code rc;
    trexio_t* trexio_file = trexio_open("../data/h2o.h5", 'r', TREXIO_AUTO, &rc);
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error: %s\n", trexio_string_of_error(rc));
        exit(1);
    }

    // read nucleus repulsion energy

    double *energy = read_nucleus_repulsion(trexio_file);
    // double energy;
    // read_nucleus_repulsion(trexio_file, &energy);
    printf("Nucleus repulsion energy: %f\n", energy);
    // // read number of up electrons
    // int32_t n_up;
    // read_electron_up_num(trexio_file, &n_up);
    // // read number of MOs
    // int32_t mo_num;
    // read_mo_num(trexio_file, &mo_num);
    // // read MO 1e integrals
    // double* data = malloc(mo_num * mo_num * sizeof(double));
    // read_mo_1e_int_core_hamiltonian(trexio_file, data);
    // // read number of 2e integrals
    // double* data2 = malloc(mo_num * mo_num * mo_num * mo_num * sizeof(double));
    // read_mo_2e_int_eri(trexio_file, data2);


    // close file
    rc = trexio_close(trexio_file);
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error: %s\n", trexio_string_of_error(rc));
        exit(1);
    }
    trexio_file = NULL;


    return 0;
}