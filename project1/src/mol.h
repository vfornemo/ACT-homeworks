#ifdef MOL_H
#define MOL_H

#include "util.h"
#include "stdin.h"

typedef double energy;


typedef struct molecule{
    int32_t n_mo;
    int32_t n_up;
    int32_t* 2e_index;
    energy* nuclear_repulsion;
    energy* 1e_hamitonian;
    energy* 2e_hamitonian;
    energy* mo_energy;
} mol;
    



#endif 
