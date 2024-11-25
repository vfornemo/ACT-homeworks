/**
 * \file reader.h
 * \brief This module contains the functions for reading the trexio file
 *
 * \author Tianyi Gao, Yifan Jiang
 * \version 1.0
 * \date 2024-11-23
 * \copyright GNU Public License V3.0
 */

#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <trexio.h>
#include "mol.h"

/**
 * @brief read the nucleus repulsion energy from the trexio file
 * 
 * @param trexio_file trexio file handler
 * @param m Mol struct
 */
void read_nucleus_repulsion(trexio_t* const trexio_file, Mol* const m);

/**
 * @brief read the number of up electrons from the trexio file
 * 
 * @param trexio_file trexio file handler
 * @param m Mol struct
 */
void read_electron_up_num(trexio_t* const trexio_file, Mol* const m);

/**
 * @brief read the number of MOs from the trexio file
 * 
 * @param trexio_file trexio file handler
 * @param m Mol struct
 */
void read_mo_num(trexio_t* const trexio_file, Mol* const m);

/**
 * @brief read the 1e integrals from the trexio file
 * 
 * @param trexio_file trexio file handler
 * @param m Mol struct
 */
void read_mo_1e_int_h_core(trexio_t* const trexio_file, Mol* const m);

/**
 * @brief read the size of 2e integrals from the trexio file
 * 
 * @param trexio_file trexio file handler
 * @param m Mol struct
 */
void read_mo_2e_int_eri_size(trexio_t* const trexio_file, Mol* const m);

/**
 * @brief read the 2e integrals from the trexio file
 * 
 * @param trexio_file trexio file handler
 * @param m Mol struct
 */
void read_mo_2e_int_eri(trexio_t* const trexio_file, Mol* const m);

/**
 * @brief read the MO energies from the trexio file
 * 
 * @param trexio_file trexio file handler
 * @param m Mol struct
 */
void read_mo_energy(trexio_t* const trexio_file, Mol* const m);

#endif
