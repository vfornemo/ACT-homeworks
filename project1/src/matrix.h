#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    double* data;
} Matrix;
    

#endif 

void print_matrix(Matrix* const m);
double sum_diag(Matrix* const m, int n);