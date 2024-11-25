#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"
#include "util.h"

void read_nucleus_repulsion(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    rc = trexio_read_nucleus_repulsion(trexio_file, &m->e_nuc);
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
    m->h_core = malloc(m->mo_num * m->mo_num * sizeof(double));

    if (m->h_core == NULL) {
        fprintf(stderr, "Malloc failed for data");
        exit(1);
    }
    rc = trexio_read_mo_1e_int_core_hamiltonian(trexio_file, m->h_core);

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
    rc = trexio_read_mo_2e_int_eri(trexio_file, 0, &m->n_2e_int, m->eri_index, m->eri_value);

    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading MO 2e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_energy(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc;
    m->e_mo = malloc(m->mo_num * sizeof(energy));
    rc = trexio_read_mo_energy(trexio_file, m->e_mo);    
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading MO energy\n%s\n",
                        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

