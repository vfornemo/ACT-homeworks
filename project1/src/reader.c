#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"

// int read_nucleus_repulsion(trexio_t* const trexio_file, double* const energy) {
//     trexio_exit_code rc; // TREXIO return code
//     // double energy; // Variable where the energy is read
//     rc = trexio_read_nucleus_repulsion(trexio_file, &energy);
//     // Check the return code to be sure reading was OK
//     if (rc != TREXIO_SUCCESS) {
//         printf("TREXIO Error reading nuclear repulsion energy:\n%s\n",
//         trexio_string_of_error(rc));
//         exit(1);
//     } else {
//         return 0;
//     }
// }

double* read_nucleus_repulsion(trexio_t* const trexio_file) {
    trexio_exit_code rc; // TREXIO return code
    double* energy = malloc(sizeof(double)); // Variable where the energy is read
    if (energy == NULL) {
        fprintf(stderr, "Malloc failed for energy");
        exit(1);
    }
    rc = trexio_read_nucleus_repulsion(trexio_file, &energy);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error reading nuclear repulsion energy:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    } else {
        return energy;
    }
}

int read_electron_up_num(trexio_t* const trexio_file, int32_t* const n_up) {
    trexio_exit_code rc; // TREXIO return code
    // int32_t n_up; // Variable where the number of up electrons is read
    rc = trexio_read_electron_up_num(trexio_file, &n_up);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error reading number of up electrons:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    } else {
        return 0;
    }
}

int read_mo_num(trexio_t* const trexio_file, int32_t* const mo_num) {
    trexio_exit_code rc; // TREXIO return code
    // int32_t mo_num; // Variable where the number of MOs is read
    rc = trexio_read_mo_num(trexio_file, &mo_num);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error reading number of MOs:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    } else {
        return 0;
    }
}

int read_mo_1e_int_core_hamiltonian(trexio_t* const trexio_file, double* const data) {
    trexio_exit_code rc; // TREXIO return code
    // double* data; // Variable where the MO 1e integrals are read
    rc = trexio_read_mo_1e_int_core_hamiltonian(trexio_file, data);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error reading MO 1e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    } else {
        return 0;
    }
}

int read_mo_2e_int_eri_size(trexio_t* const trexio_file, int64_t* const n_integrals) {
    trexio_exit_code rc; // TREXIO return code
    // int64_t n_integrals; // Variable where the number of 2e integrals is read
    rc = trexio_read_mo_2e_int_eri_size(trexio_file, &n_integrals);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error reading number of 2e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    } else {
        return 0;
    }
}

int read_mo_2e_int_eri(trexio_t* const trexio_file, double* const data) {
    //get the size of the 2e integrals
    int64_t n_integrals;
    read_mo_2e_int_eri_size(trexio_file, &n_integrals);

    // allocate memory
    int32_t* const index = malloc(4 * n_integrals * sizeof(int32_t));
    if (index == NULL) {
        fprintf(stderr, "Malloc failed for index");
        exit(1);
    }
    double* const value = malloc(n_integrals * sizeof(double));
    if (value == NULL) {
        fprintf(stderr, "Malloc failed for value");
        exit(1);
    }

    trexio_exit_code rc; // TREXIO return code
    // double* data; // Variable where the MO 2e integrals are read
    rc = trexio_read_mo_2e_int_eri(trexio_file, 0, n_integrals, index, value);

    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error reading MO 2e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    } else {
        return 0;
    }
}

int get_nth_eri(int64_t n, int32_t* const index, double* const value, double* const integral) {
    int i = index[4 * n];
    int j = index[4 * n + 1];
    int k = index[4 * n + 2];
    int l = index[4 * n + 3];
    *integral = value[n];

    return 0;
}