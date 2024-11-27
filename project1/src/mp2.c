/**
 * @file mp2.c
 * @author Yifan Jiang
 * @brief This module contains the functions for MP2 energy calculation
 * @version 1.0
 * @date 2024-11-25
 * 
 * @copyright GNU Public License V3.0
 * 
 */

#include "mp2.h"

void cal_mp2_correlation(Mol* const m) {
    m->e_mp2 = 0;
    for (int32_t i = 0; i < m->n_up; ++i) {
        for (int32_t j = 0; j < m->n_up; ++j) {
            for (int32_t a = m->n_up; a < m->mo_num; ++a) {
                for (int32_t b = a; b < m->mo_num; ++b) {
                    energy denominator = m->e_mo[i] + m->e_mo[j] - m->e_mo[a] - m->e_mo[b];
                    if (a == b) {
                        energy ijab;
                        if (i > j) {
                            ijab = get_eri_energy(m, b, a, i, j);
                        } else {
                            ijab = get_eri_energy(m, b, a, j, i);
                        }
                        m->e_mp2 += ijab * ijab / denominator;
                        // printf("%f, %f\n", ijab, ijab * ijab / denominator);
                    } else { 
                        energy ijab = get_eri_energy(m, b, a, j, i);
                        energy ijba = get_eri_energy(m, b, a, i, j);
                        m->e_mp2 += ((ijab * (2 * ijab - ijba)) + (ijba * (2 * ijba - ijab))) / denominator;

                        // printf("%f, %f\n", ijab, ijba);
                    }
                    // printf("%f\n", m->e_mp2);
                    // printf("%f, %f, %f, %f\n", m->e_mo[i],
                    //                         m->e_mo[j],
                    //                         m->e_mo[a],
                    //                         m->e_mo[b]);
                }
            }
        }
    }
    return;
}