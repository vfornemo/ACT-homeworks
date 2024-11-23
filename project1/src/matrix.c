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