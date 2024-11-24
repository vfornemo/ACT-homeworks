# include <stdio.h>  
#include <stdlib.h>
# include "matrix.h"

// int init_matrix(Matrix* const m, int row, int col) {
//     m->row = row;
//     m->col = col;
//     m->data = malloc(row * col * sizeof(double));
//     if (m->data == NULL) {
//         fprintf(stderr, "Malloc failed for data");
//         return 1;
//     }
//     return 0;
// }

void print_matrix(Matrix* const m) {
    for (int i = 0; i < m->row; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < m->col; j++) {
            printf("%f ", m->data[i * m->col + j]);
        }
        printf("\n");
    }
}

/* Sum to nth diagonal elements of a square matrix */
double sum_diag(Matrix* const m, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += m->data[i * m->col + i];
    }
    return sum;

    // test sum_diag
    // Matrix m1 = {3, 3, (double[]){1, 2, 3, 4, 5, 6, 7, 8, 9}};
    // double sum = sum_diag(&m1, 3);
    // printf("Sum of diagonal elements: %f\n", sum);
    // double sum2 = sum_diag(&m1, 2);
    // printf("Sum of diagonal elements: %f\n", sum2);
}