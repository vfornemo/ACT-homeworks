#ifndef MOL_H
#define MOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef double energy;

typedef struct {
    // number of MOs
    int32_t mo_num;
    // number of up electrons (or down electrons for RHF)
    int32_t n_up;
    // number of 2e integrals
    int64_t n_2e_int;
    // nucleus repulsion energy
    energy e_nuc;
    // 2e integrals
    int32_t* eri_index;
    // 2e integrals values
    energy* eri_value;
    // 2e integrals in unique index sequence
    energy* eri_seq;
    // 1e integrals
    energy* h_core;
    // sum of diagonal elements of h_core
    energy* e_mo;
    energy h_core_sum;
    // sum of eri values
    energy eri_sum;
    // electronic energy
    energy e_elec;
    // HF energy
    energy e_hf;
    // MP2 energy
    energy e_mp2;
} Mol;

void mol_init(Mol* const m, char* filename);
void mol_destruct(Mol* const m);

energy get_nth_eri(int64_t n, Mol* const m);
void gen_eri_index(Mol* const m);

energy get_eri_energy(Mol* const m, int32_t i, int32_t j, int32_t a, int32_t b);


#endif

