/**
 * \file mp2.h
 * \brief This module contains the functions for MP2 energy calculation
 *
 * \author Yifan Jiang
 * \version 1.0
 * \date 2024-11-25
 * \copyright GNU Public License V3.0
 */

#ifndef MP2_H
#define MP2_H

#include "mol.h"

/**
 * @brief Calculate the MP2 correlation energy
 * 
 * @param m Mol struct
 */
void cal_mp2_correlation(Mol* const m);

#endif