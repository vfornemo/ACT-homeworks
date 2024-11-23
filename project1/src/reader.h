#include <stdio.h>
#include <trexio.h>

// int read_nucleus_repulsion(trexio_t* const trexio_file, double* const energy);
double* read_nucleus_repulsion(trexio_t* const trexio_file);
int read_electron_up_num(trexio_t* const trexio_file, int32_t* const n_up);
int read_mo_num(trexio_t* const trexio_file, int32_t* const mo_num);
int read_mo_1e_int_core_hamiltonian(trexio_t* const trexio_file, double* const data);
int read_mo_2e_int_eri_size(trexio_t* const trexio_file, int64_t* const n_integrals);
int read_mo_2e_int_eri(trexio_t* const trexio_file, double* const data);
int get_nth_eri(int64_t n, int32_t* const index, double* const value, double* const integral);