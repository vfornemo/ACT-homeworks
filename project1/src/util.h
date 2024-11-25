#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>  
#include <stdlib.h>
#include "mol.h"

void print_matrix(double* const m, int row, int col);
/* Sum to nth diagonal elements of a square matrix */
double sum_diag(double* const m, int n, int order);

int32_t index_2e(int i, int j, int k, int l, int n);


#endif