#include <stdio.h>
#include <stdlib.h>
#include "mol.h"
#include "matrix.h"
#include "reader.h"

void mol_init(Mol* const m, char* filename) {
    // initialize mol struct
    trexio_exit_code rc;
    trexio_t* trexio_file = trexio_open(filename, 'r', TREXIO_AUTO, &rc);
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error: %s\n", trexio_string_of_error(rc));
        exit(1);
    }

    // read nucleus repulsion energy
    read_nucleus_repulsion(trexio_file, m);
    printf("Nucleus repulsion energy: %f\n", *m->e_nuc);
    // read number of up electrons
    read_electron_up_num(trexio_file, m);
    printf("Number of up electrons: %d\n", m->n_up);
    // read number of MOs
    read_mo_num(trexio_file, m);
    printf("Number of MOs: %d\n", m->mo_num);
    // read MO 1e integrals
    read_mo_1e_int_h_core(trexio_file, m);
    print_matrix(m->h_core);
    // read number of 2e integrals
    read_mo_2e_int_eri(trexio_file, m);
    printf("Number of 2e integrals: %ld\n", m->n_2e_int);
    for (int i = 0; i < m->n_2e_int; i++) {
        double integ = get_nth_eri(i, m);
    }

    // close file
    rc = trexio_close(trexio_file);
    if (rc != TREXIO_SUCCESS) {
        printf("TREXIO Error: %s\n", trexio_string_of_error(rc));
        exit(1);
    }
    trexio_file = NULL;

    return;
}

void mol_destruct(Mol* const m) {
    if (m->e_nuc != NULL) {
        free(m->e_nuc);
	    m->e_nuc = NULL;
    }
    if (m->eri_index != NULL) {
        free(m->eri_index);
	    m->eri_index = NULL;
    }
    if (m->eri_value != NULL) {
        free(m->eri_value);
	    m->eri_value = NULL;
    }
    if (m->h_core != NULL) {
        free(m->h_core->data);
        m->h_core->data = NULL;
        free(m->h_core);
        m->h_core = NULL;
    }
    if (m->h_core_sum != NULL) {
        free(m->h_core_sum);
        m->h_core_sum = NULL;
    }
    if (m->eri_sum != NULL) {
        free(m->eri_sum);
        m->eri_sum = NULL;
    }
    if (m->e_elec != NULL) {
        free(m->e_elec);
        m->e_elec = NULL;
    }
    if (m->e_hf != NULL) {
        free(m->e_hf);
        m->e_hf = NULL;
    }
    return;
}
    
