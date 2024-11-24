#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"
#include "matrix.h"

void get_hcore_sum(Mol* const m) {
    m->h_core_sum = malloc(sizeof(double));
    if (m->h_core_sum == NULL) {
        fprintf(stderr, "Malloc failed for h_core_sum");
        exit(1);
    }
    *m->h_core_sum = 2.0 * sum_diag(m->h_core, m->n_up);
    return;
}

/* HF ERI should be <ij|ij> or <ij|ji>, for <ij|kl>, check if i == k and j == l
or i == l and j == k. 
if i = j = k = l, return 1
if i = k and j = l, return 2
if i = l and j = k, return 3
else return 0
*/

int match_eri(int i, int j, int k, int l, Mol* const m) {
    // check if i, j, k, l > n_up
    if (i >= m->n_up || j >= m->n_up || k >= m->n_up || l >= m->n_up) {
        return 0;
    }

    if (i == k && j == l) {
        if (i == j) {
            // printf("iiii, i, j, k, l: %d, %d, %d, %d\n", i, j, k, l);
            return 1;
        } else {
            // printf("ijij, i, j, k, l: %d, %d, %d, %d\n", i, j, k, l);
            return 2;
        }
    } 

    if (i == j && l == k) {
        // printf("ijji, i, j, k, l: %d, %d, %d, %d\n", i, j, k, l);
        return 3;
    } else if (i == l && j == k) {
        // printf("ijji, i, j, k, l: %d, %d, %d, %d\n", i, j, k, l);
        return 3;
    } else {
        return 0;
    }
}

void get_eri_sum(Mol* const m) {
    m->eri_sum = malloc(sizeof(double));
    if (m->eri_sum == NULL) {
        fprintf(stderr, "Malloc failed for eri_sum");
        exit(1);
    }
    *m->eri_sum = 0.0;
    for (int i = 0; i < m->n_2e_int; i++) {
        int x = match_eri(m->eri_index[4 * i], m->eri_index[4 * i + 1], m->eri_index[4 * i + 2], m->eri_index[4 * i + 3], m);
        switch(x) {
            case 1:
                // printf("x: %d, eri = %f\n", x, m->eri_value[i]);
                *m->eri_sum += 1.0 * m->eri_value[i];
                break;
            case 2:
                // printf("x: %d, eri = %f\n", x, m->eri_value[i]);
                *m->eri_sum += 4.0 * m->eri_value[i];
                break;
            case 3:
                // printf("x: %d, eri = %f\n", x, m->eri_value[i]);
                *m->eri_sum -= 2.0 * m->eri_value[i];
                break;
            default:
                break;
        }
    }
    return;
}


void hf_kernel(Mol* const m) {
    // HF energy
    // E_tot = E_nuc + E_elec
    // E_elec = 2 * h_core + sum_ij(2 * (eri(ij) - eri(ji)))
    
    get_hcore_sum(m);
    printf("h_core_sum: %f\n", *m->h_core_sum);
    get_eri_sum(m);
    printf("eri_sum: %f\n", *m->eri_sum);
    m->e_elec = malloc(sizeof(double));
    if (m->e_elec == NULL) {
        fprintf(stderr, "Malloc failed for e_elec");
        exit(1);
    }
    *m->e_elec = (*m->h_core_sum) + *m->eri_sum;

    m->e_hf = malloc(sizeof(double));
    if (m->e_hf == NULL) {
        fprintf(stderr, "Malloc failed for hf_energy");
        exit(1);
    }
    *m->e_hf = *m->e_nuc + *m->e_elec;

    return;
}