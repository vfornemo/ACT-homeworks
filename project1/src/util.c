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

/* Sum to nth diagonal elements of a square matrix */
double sum_diag(double* const m, int n, int order) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += m[i * order + i];
    }
    return sum;

    // test sum_diag
    // Matrix m1 = {3, 3, (double[]){1, 2, 3, 4, 5, 6, 7, 8, 9}};
    // double sum = sum_diag(&m1, 3);
    // printf("Sum of diagonal elements: %f\n", sum);
    // double sum2 = sum_diag(&m1, 2);
    // printf("Sum of diagonal elements: %f\n", sum2);
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