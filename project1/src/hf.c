/**
 * @file hf.c
 * @author Tianyi Gao
 * @brief This module contains the functions for HF energy calculation
 * @version 1.0
 * @date 2024-11-25
 * 
 * @copyright GNU Public License V3.0
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"
#include "util.h"

void get_hcore_sum(Mol* const m) {
    m->h_core_sum = 2.0 * sum_diag(m->h_core, m->n_up, m->mo_num);
    return;
}



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
    m->eri_sum = 0.0;
    for (int i = 0; i < m->n_2e_int; i++) {
        int x = match_eri(m->eri_index[4 * i], m->eri_index[4 * i + 1], m->eri_index[4 * i + 2], m->eri_index[4 * i + 3], m);
        switch(x) {
            case 1:
                // printf("x: %d, eri = %f\n", x, m->eri_value[i]);
                m->eri_sum += 1.0 * m->eri_value[i];
                break;
            case 2:
                // printf("x: %d, eri = %f\n", x, m->eri_value[i]);
                m->eri_sum += 4.0 * m->eri_value[i];
                break;
            case 3:
                // printf("x: %d, eri = %f\n", x, m->eri_value[i]);
                m->eri_sum -= 2.0 * m->eri_value[i];
                break;
            default:
                break;
        }
    }
    // for (int32_t i = 0; i < m->n_up; ++i) {
    //     for (int32_t j = i; j < m->n_up; ++j) {
    //         energy ijij
    //     }
    // }
    return;
}


void hf_kernel(Mol* const m) {
    // HF energy
    // E_tot = E_nuc + E_elec
    // E_elec = 2 * h_core + sum_ij(2 * (eri(ij) - eri(ji)))
    
    get_hcore_sum(m);
    printf("h_core_sum: %f\n", m->h_core_sum);
    get_eri_sum(m);
    printf("eri_sum: %f\n", m->eri_sum);
    m->e_elec = m->h_core_sum + m->eri_sum;
    m->e_hf = m->e_nuc + m->e_elec;

    return;
}