
/**
 * \file util.h
 * \brief This module contains the utility functions
 *
 * \author Tianyi Gao
 * \version 1.0
 * \date 2024-11-23
 * \copyright GNU Public License V3.0
 */

#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>  
#include <stdlib.h>
#include "mol.h"

/**
 * @brief print a double array in matrix format
 * 
 * @param m array to be printed
 * @param row number of rows
 * @param col number of columns
 */
void print_matrix(double* const m, int row, int col);
/**
 * @brief sum to nth diagonal elements of a square matrix
 * 
 * @param m 1D matrix data array
 * @param n sum up to nth diagonal elements
 * @param order order of the matrix (row = col)
 * @return sum of the diagonal elements
 */
double sum_diag(double* const m, int n, int order);

/**
 * @brief calculates unique index of given (ijkl) for 2e integrals
 * @note 0 <= i, j, k, l < n
 * @note i <= j, k <= l, i <= k
 * @note if i == k, then j <= l
 * @param i, j, k, l indices of the 2e integrals
 * @param n number of MOs 
 * @return unique index
 */
int32_t index_2e(int i, int j, int k, int l, int n);

#endif