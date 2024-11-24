#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"

int main() {

    // initialize mol struct
    Mol m = {0, 0, 0, NULL, NULL, NULL};
    char* path = "./data/h2o.h5";
    mol_init(&m, path);
    mol_destruct(&m);
    

    return 0;
}
