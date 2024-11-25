/**
 * \file mol.h
 * \brief This module contains the Mol struct and functions for Mol struct
 *
 * \author Yifan Jiang, Tianyi Gao
 * \version 1.0
 * \date 2024-11-23
 * \copyright GNU Public License V3.0
 */

#ifndef MOL_H
#define MOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef double energy;

/** \struct Mol
 *  \brief Mol struct contains all the information of the molecule
 */
typedef struct {
    int32_t mo_num;        //!< number of MOs
    int32_t n_up;          //!< number of up electrons (or down electrons for RHF)
    int64_t n_2e_int;      //!< number of 2e integrals
    energy e_nuc;          //!< nucleus repulsion energy
    int32_t* eri_index;    //!< 2e integrals index
    energy* eri_value;     //!< 2e integrals values
    energy* eri_seq;       //!< 2e integrals in unique index sequence
    energy* h_core;        //!< 1e integrals
    energy* e_mo;          //!< MO energies
    energy h_core_sum;     //!< sum of diagonal elements of h_core
    energy eri_sum;        //!< sum of eri values
    energy e_elec;         //!< electronic energy
    energy e_hf;           //!< HF energy
    energy e_mp2;          //!< MP2 energy
} Mol;

/**
 * @brief initialize the Mol struct from the .h5 file
 * 
 * @param m Mol struct
 * @param filename path to the .h5 file
 */
void mol_init(Mol* const m, char* filename);

/**
 * @brief destruct the Mol struct
 * 
 * @param m Mol struct
 */
void mol_destruct(Mol* const m);

/**
 * @brief get the nth 2e integral value
 * 
 * @param n index of the 2e integral
 * @param m Mol struct
 * @return nth 2e integral value
 */
energy get_nth_eri(int64_t n, Mol* const m);

/**
 * @brief extract the 2e integral value into a 1D array, with unique index sequence
 * 
 * @param m 
 */
void gen_eri_index(Mol* const m);

/**
 * @brief Given (ijab), return the 2e integral energy of (ia|jb)
 * 
 * @param m Mol struct
 * @param i, j, a, b indices of the 2e integral 
 * @return 2e integral of (ia|jb)
 */
energy get_eri_energy(Mol* const m, int32_t i, int32_t j, int32_t a, int32_t b);


#endif

