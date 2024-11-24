#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include "reader.h"
#include "mol.h"

void read_nucleus_repulsion(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    m->e_nuc = malloc(sizeof(double)); // Variable where the energy is read
    if (m->e_nuc == NULL) {
        fprintf(stderr, "Malloc failed for energy");
        exit(1);
    }
    rc = trexio_read_nucleus_repulsion(trexio_file, m->e_nuc);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading nuclear repulsion energy:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    } 
    return;
}

void read_electron_up_num(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    rc = trexio_read_electron_up_num(trexio_file, &m->n_up);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading number of up electrons:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_num(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    rc = trexio_read_mo_num(trexio_file, &m->mo_num);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading number of MOs:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_1e_int_h_core(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    m->h_core = malloc(sizeof(Matrix));
    m->h_core->data = malloc(m->mo_num * m->mo_num * sizeof(double));

    if (m->h_core->data == NULL) {
        fprintf(stderr, "Malloc failed for data");
        exit(1);
    }
    rc = trexio_read_mo_1e_int_core_hamiltonian(trexio_file, m->h_core->data);
    m->h_core->row = m->mo_num;
    m->h_core->col = m->mo_num;

    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading MO 1e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_2e_int_eri_size(trexio_t* const trexio_file, Mol* const m) {
    trexio_exit_code rc; // TREXIO return code
    rc = trexio_read_mo_2e_int_eri_size(trexio_file, &m->n_2e_int);
    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading number of 2e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

void read_mo_2e_int_eri(trexio_t* const trexio_file, Mol* const m) {

    read_mo_2e_int_eri_size(trexio_file, m);
    // allocate memory
    m->eri_index = malloc(4 * m->n_2e_int * sizeof(int32_t));
    if (m->eri_index == NULL) {
        fprintf(stderr, "Malloc failed for index");
        exit(1);
    }
    m->eri_value = malloc(m->n_2e_int * sizeof(double));
    if (m->eri_value == NULL) {
        fprintf(stderr, "Malloc failed for value");
        exit(1);
    }

    trexio_exit_code rc; // TREXIO return code
    rc = trexio_read_mo_2e_int_eri(trexio_file, 0, &m->n_2e_int, m->eri_index, m->eri_value);

    // Check the return code to be sure reading was OK
    if (rc != TREXIO_SUCCESS) {
        fprintf(stderr, "TREXIO Error reading MO 2e integrals:\n%s\n",
        trexio_string_of_error(rc));
        exit(1);
    }
    return;
}

energy get_nth_eri(int64_t n, Mol* const m) {
    int i = m->eri_index[4 * n];
    int j = m->eri_index[4 * n + 1];
    int k = m->eri_index[4 * n + 2];
    int l = m->eri_index[4 * n + 3];
    energy integral = m->eri_value[n];
    printf("%ld th ERI(%d, %d, %d, %d) = %f\n", n, i, j, k, l, integral);
    return integral;
}

int index_2e(int i, int j, int k, int l, int n) {
    return (k - 1) * (n - 1) - (k - 1) * (k - 2) / 2 + l 
        + n * (n + 1) * (j - 1) / 2 - j * (j - 1) / 2 
        + (i - 1) * (n * (n * (n - 1) / 2 + 1) - j * (n - 1) - 1) 
        + (i - 1) * (i - 2) / 2 * (j - (n * (3 * n - 7) / 2 - 4)) 
        + (i - 1) * (i - 2) * (i - 3) / 2 * (n - 2) - (i - 1) * (i - 2) * (i - 3) * (i - 4) / 8;
}


/* 
test index
    // test index function
 
    int n = m.mo_num;
    for (int i = 1; i<n; i++) {
        int k = i;
        for (int j = i; j<n; j++) {
            for (int l = j; l<n; l++) {
                int index = index_2e(i, j, k, l, n);
                printf("i, j, k, l, index = %d, %d, %d, %d, %d\n", i, j, k, l, index);
            }
        }
        for (int k = i+1; k<n; k++) {
            for (int j = i; j<n; j++) {
                for (int l = k; l<n; l++) {
                    int index = index_2e(i, j, k, l, n);
                    printf("i, j, k, l, index = %d, %d, %d, %d, %d\n", i, j, k, l, index);
                }
            }
        }
    }
 */


/* 
another index

      subroutine index2(i,j,k,l,n, index)
      implicit none
      integer:: i,j,k,l,n, index
      index = 0.125*(-i*i*i*i + i*i*i*(4*n+2) + i*i*(4*j-2*n*(3*n+5)-3) + 2*i*(2*n+1)*(-2*j+n*(n+3)+1) &
      & -4*(j*j-j*(n*(n+3)+1)+n*(n*(n+3)-2*k)+(k-1)*k-2*l+4*n))
      end subroutine index2

 */