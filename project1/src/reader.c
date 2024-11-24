#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"

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

void read_nucleus_repulsion(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    m->e_nuc = malloc(sizeof(double)); // Variable where the energy is read
    if (m->e_nuc == NULL) {
        fprintf(stderr, "Malloc failed for energy");
        exit(1);
    }
    rc = trexio_read_nucleus_repulsion(trexio_file, m->e_nuc);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading nuclear repulsion energy:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    } 
    return;
}

void read_electron_up_num(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    // int32_t n_up; // Variable where the number of up electrons is read
    rc = trexio_read_electron_up_num(trexio_file, &m->n_up);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading number of up electrons:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_num(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    // int32_t mo_num; // Variable where the number of MOs is read
    rc = trexio_read_mo_num(trexio_file, &m->mo_num);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading number of MOs:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_1e_int_h_core(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    // double* data; // Variable where the MO 1e integrals are read
    m->h_core = malloc(sizeof(Matrix));
    m->h_core->data = malloc(m->mo_num * m->mo_num * sizeof(double));

    if (m->h_core->data == NULL) {
        fprintf(stderr, "Malloc failed for data");
        exit(1);
    }
    rc = trexio_read_mo_1e_int_core_hamiltonian(trexio_file, m->h_core->data);
    m->h_core->row = m->mo_num;
    m->h_core->col = m->mo_num;

    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading MO 1e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_2e_int_eri_size(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    // int64_t n_2e_int; // Variable where the number of 2e integrals is read
    rc = trexio_read_mo_2e_int_eri_size(trexio_file, &m->n_2e_int);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading number of 2e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_2e_int_eri(trexio_t* const trexio_file, Mol* const m) {

    read_mo_2e_int_eri_size(trexio_file, m);
    // allocate memory
    m->eri_index = malloc(4 * m->n_2e_int * sizeof(int32_t));
    if (m->eri_index == NULL) {
        fprintf(stderr, "Malloc failed for index");
        exit(1);
    }
    m->eri_value = malloc(m->n_2e_int * sizeof(double));
    if (m->eri_value == NULL) {
        fprintf(stderr, "Malloc failed for value");
        exit(1);
    }

    trexio_exit_code rc; // TREXIO return code
    // double* data; // Variable where the MO 2e integrals are read
    rc = trexio_read_mo_2e_int_eri(trexio_file, 0, &m->n_2e_int, m->eri_index, m->eri_value);

    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading MO 2e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

energy get_nth_eri(int64_t n, Mol* const m) {
    int i = m->eri_index[4 * n];
    int j = m->eri_index[4 * n + 1];
    int k = m->eri_index[4 * n + 2];
    int l = m->eri_index[4 * n + 3];
    energy integral = m->eri_value[n];

    return integral;
}
