#ifndef HF_H
#define HF_H

#include <stdio.h>
#include <stdlib.h>
#include "mol.h"
#include "util.h"

void get_hcore_sum(Mol* const m);

void hf_kernel(Mol* const m);

int match_eri(int i, int j, int k, int l, Mol* const m);

void get_eri_sum(Mol* const m);

#endif