#include <stdio.h>
#include <stdlib.h>
#include "mol.h"
#include "reader.h"
#include "util.h"

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
    printf("Nucleus repulsion energy: %f\n", m->e_nuc);
    // read number of up electrons
    read_electron_up_num(trexio_file, m);
    printf("Number of up electrons: %d\n", m->n_up);
    // read number of MOs
    read_mo_num(trexio_file, m);
    printf("Number of MOs: %d\n", m->mo_num);
    // read MO 1e integrals
    read_mo_1e_int_h_core(trexio_file, m);
    print_matrix(m->h_core, m->mo_num, m->mo_num);
    // read number of 2e integrals
    read_mo_2e_int_eri(trexio_file, m);
    printf("Number of 2e integrals: %ld\n", m->n_2e_int);
    // for (int i = 0; i < m->n_2e_int; i++) {
    //     double integ = get_nth_eri(i, m);
    // }

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
    if (m->eri_index != NULL) {
        free(m->eri_index);
	    m->eri_index = NULL;
    }
    if (m->eri_value != NULL) {
        free(m->eri_value);
	    m->eri_value = NULL;
    }
    if (m->h_core != NULL) {
        free(m->h_core);
        m->h_core = NULL;
    }
    return;
}

energy get_nth_eri(int64_t n, Mol* const m) {
    int i = m->eri_index[4 * n];
    int j = m->eri_index[4 * n + 1];
    int k = m->eri_index[4 * n + 2];
    int l = m->eri_index[4 * n + 3];
    energy integral = m->eri_value[n];
    printf("%ld th ERI(%d, %d, %d, %d) = %f\n", n, i, j, k, l, integral);
    return integral;
}

    
void gen_eri_index(Mol* const m) {
    int max_idx = index_2e(m->mo_num, m->mo_num, m->mo_num, m->mo_num, m->mo_num);
    double *eri = malloc(max_idx * sizeof(double));
    // initialize eri
    for (int i = 0; i < max_idx; i++) {
        eri[i] = 0.0;
    }

    for (int n = 0; n < m->n_2e_int; n++) {
        int i = m->mo_num - m->eri_index[4 * n];
        int k = m->mo_num - m->eri_index[4 * n + 1];
        int j = m->mo_num - m->eri_index[4 * n + 2];
        int l = m->mo_num - m->eri_index[4 * n + 3];
        if (i>j || i>k || k>l || (i == k && j > l)) {
            printf("warning: index condition not satisfied\n");
        } else {
            int idx = index_2e(i, j, k, l, m->mo_num);
            printf("i, j, k, l, idx = %d, %d, %d, %d, %d\n", i, j, k, l, idx);
            eri[idx] = m->eri_value[n];
        }
    }
    m->eri_seq = eri;
    return;
}