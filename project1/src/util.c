/**
 * @file util.c
 * @author Tianyi Gao
 * @brief This module contains the utility functions
 * @version 1.0
 * @date 2024-11-23
 * 
 * @copyright GNU Public License V3.0
 * 
 */

#include <stdio.h>  
#include <stdlib.h>
#include "util.h"
#include "mol.h"

void print_matrix(double* const m, int row, int col) {
    for (int i = 0; i < row; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < col; j++) {
            printf("%f ", m[i * col + j]);
        }
        printf("\n");
    }
}

double sum_diag(double* const m, int n, int order) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += m[i * order + i];
    }
    return sum;

}

inline int32_t index_2e(int i, int j, int k, int l, int n) {
    return (k - 1) * (n - 1) - (k - 1) * (k - 2) / 2 + l 
        + n * (n + 1) * (j - 1) / 2 - j * (j - 1) / 2 
        + (i - 1) * (n * (n * (n - 1) / 2 + 1) - j * (n - 1) - 1) 
        + (i - 1) * (i - 2) / 2 * (j - (n * (3 * n - 7) / 2 - 4)) 
        + (i - 1) * (i - 2) * (i - 3) / 2 * (n - 2) - (i - 1) * (i - 2) * (i - 3) * (i - 4) / 8;
}

/* 
another index

      subroutine index2(i,j,k,l,n, index)
      implicit none
      integer:: i,j,k,l,n, index
      index = 0.125*(-i*i*i*i + i*i*i*(4*n+2) + i*i*(4*j-2*n*(3*n+5)-3) + 2*i*(2*n+1)*(-2*j+n*(n+3)+1) &
      & -4*(j*j-j*(n*(n+3)+1)+n*(n*(n+3)-2*k)+(k-1)*k-2*l+4*n))
      end subroutine index2

 */