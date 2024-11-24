#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <trexio.h>
#include "mol.h"

void read_nucleus_repulsion(trexio_t* const trexio_file, Mol* const m);

void read_electron_up_num(trexio_t* const trexio_file, Mol* const m);

void read_mo_num(trexio_t* const trexio_file, Mol* const m);

void read_mo_1e_int_h_core(trexio_t* const trexio_file, Mol* const m);

void read_mo_2e_int_eri_size(trexio_t* const trexio_file, Mol* const m);

void read_mo_2e_int_eri(trexio_t* const trexio_file, Mol* const m);

void read_mo_energy(trexio_t* const trexio_file, Mol* const m);

#endif
