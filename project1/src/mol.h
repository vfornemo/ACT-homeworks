#ifndef MOL_H
#define MOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "matrix.h"

typedef double energy;

typedef struct {
    int32_t mo_num;
    int32_t n_up;
    int64_t n_2e_int;
    energy* e_nuc;
    Matrix* h_core;
    int32_t* eri_index;
    energy* eri_value;
    // energy* mo_energy;
} Mol;
    
#endif 

int mol_init(Mol* const m);
