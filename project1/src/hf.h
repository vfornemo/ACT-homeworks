/**
 * \file hf.h
 * \brief This module contains the functions for HF energy calculation
 *
 * \author Tianyi Gao
 * \version 1.0
 * \date 2024-11-24
 * \copyright GNU Public License V3.0
 */

#ifndef HF_H
#define HF_H

#include <stdio.h>
#include <stdlib.h>
#include "mol.h"
#include "util.h"

/**
 * @brief Get the core Hamiltonian sum
 * 
 * @param m Mol struct
 */
void get_hcore_sum(Mol* const m);

/**
 * @brief Calculate the HF energy
 * 
 * @param m Mol struct
 */
void hf_kernel(Mol* const m);

/**
 * @brief Match the ERI index
 * HF ERI should be <ij|ij> or <ij|ji>, for <ij|kl>, check if i == k and j == l or i == l and j == k. 
 * 
 * @param i 
 * @param j 
 * @param k 
 * @param l 
 * @param m 
 * @return 1 if i = j = k = l \\
 * @return 2 if i = k and j = l \\
 * @return 3 if i = l and j = k \\
 * @return 0 if none of the above
 */
int match_eri(int i, int j, int k, int l, Mol* const m);

/**
 * @brief Get sum of ERI values
 * 
 * @param m Mol struct
 */
void get_eri_sum(Mol* const m);

#endif
