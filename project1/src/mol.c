#include <stdio.h>
#include <stdlib.h>
#include "mol.h"
#include "matrix.h"

int mol_init(Mol* const m) {
    // initialize mol struct
    m->mo_num = 0;
    m->n_up = 0;
    m->n_2e_int = 0;
    energy* e_nuc;
    Matrix* h_core;
    energy* eri_value;
    int32_t* eri_index;
    m->e_nuc = e_nuc;
    m->h_core = h_core;
    m->eri_value = eri_value;
    m->eri_index = eri_index;

    return 0;
}