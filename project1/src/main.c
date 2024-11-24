#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"
#include "matrix.h"
#include "hf.h"

int main() {

    // initialize mol struct
    Mol m = {0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    char* path = "./data/h2o.h5";
    mol_init(&m, path);

    // HF kernel
    hf_kernel(&m);

    printf("Electronic energy: %f\n", *m.e_elec);
    printf("HF energy: %f\n", *m.e_hf);

    

    // if m not in use, free memory
    // mol_destruct(&m);
    
    return 0;
}
