/**
 * \file main.c
 * \brief This program reads the `.h5` file and computes the MP2 energy.
 * 
 * \author Yifan Jiang, Tianyi Gao
 * \version 1.0
 * \date 2024-11-25
 * \copyright GNU Public License V3.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"
#include "util.h"
#include "hf.h"
#include "mp2.h"

//! Application entry
int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Error: wrong number of arguments provided\n");
        exit(1);
    } else {
        printf("Reading file: %s\n", argv[1]);
    }
    char* path = argv[1];

    // initialize mol struct
    Mol m = {0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0}; 
    mol_init(&m, path);

    // HF kernel
    hf_kernel(&m);

    gen_eri_index(&m);

    cal_mp2_correlation(&m);
    // print eri_seq
    // int idx_max = index_2e(m.mo_num, m.mo_num, m.mo_num, m.mo_num, m.mo_num);
    // for (int i = 0; i < idx_max; i++) {
    //     printf("eri_seq[%d] = %f\n", i, m.eri_seq[i]);
    // }

    // for (int i = 0; i < m.n_up; ++i) {
    //     printf("%f\n", m.e_mo[i]);
    // }
    // printf("%f", get_eri_energy(&m, 12, 1, 0, 0));
    // for (int32_t i = 0; i < m.n_2e_int; ++i) {
    //     printf("%d, %d, %d, %d, %f\n", m.eri_index[i * 4], 
    //                                 m.eri_index[4 * i + 1],
    //                                 m.eri_index[4 * i + 2],
    //                                 m.eri_index[4 * i + 3],
    //                                 m.eri_value[i]);
    // }

    printf("Electronic energy: %f\n", m.e_elec);
    printf("HF energy: %f\n", m.e_hf);
    printf("MP2 energy: %f\n", m.e_mp2 + m.e_hf);

    // if m not in use, free memory
    mol_destruct(&m);
    
    return 0;
}
