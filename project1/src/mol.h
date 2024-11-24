#ifndef MOL_H
#define MOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "matrix.h"

typedef double energy;

typedef struct {
    // number of MOs
    int32_t mo_num;
    // number of up electrons (or down electrons for RHF)
    int32_t n_up;
    // number of 2e integrals
    int64_t n_2e_int;
    // nucleus repulsion energy
    energy* e_nuc;
    // 2e integrals
    int32_t* eri_index;
    // 2e integrals values
    energy* eri_value;
    // 1e integrals
    Matrix* h_core;
    // sum of diagonal elements of h_core
    energy* h_core_sum;
    // sum of eri values
    energy* eri_sum;
    // electronic energy
    energy* e_elec;
    // HF energy
    energy* e_hf;

} Mol;
    
#endif 

void mol_init(Mol* const m, char* filename);
void mol_destruct(Mol* const m);
