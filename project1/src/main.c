#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"
#include "util.h"
#include "hf.h"

int main() {

    // initialize mol struct
    Mol m = {0, 0, 0, 0, NULL, NULL, NULL, 0, 0, 0, 0}; 
    char* path = "./data/h2o.h5";
    mol_init(&m, path);

    // HF kernel
    hf_kernel(&m);

    gen_eri_index(&m);

    // print eri_seq
    int idx_max = index_2e(m.mo_num, m.mo_num, m.mo_num, m.mo_num, m.mo_num);
    for (int i = 0; i < idx_max; i++) {
        printf("eri_seq[%d] = %f\n", i, m.eri_seq[i]);
    }

    printf("Electronic energy: %f\n", m.e_elec);
    printf("HF energy: %f\n", m.e_hf);

    // if m not in use, free memory
    // mol_destruct(&m);
    
    return 0;
}
