/**************************************************************************************************
*                                                                                                 *
* This file is part of HPMPC.                                                                     *
*                                                                                                 *
* HPMPC -- Library for High-Performance implementation of solvers for MPC.                        *
* Copyright (C) 2014 by Technical University of Denmark. All rights reserved.                     *
*                                                                                                 *
* HPMPC is free software; you can redistribute it and/or                                          *
* modify it under the terms of the GNU Lesser General Public                                      *
* License as published by the Free Software Foundation; either                                    *
* version 2.1 of the License, or (at your option) any later version.                              *
*                                                                                                 *
* HPMPC is distributed in the hope that it will be useful,                                        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                            *
* See the GNU Lesser General Public License for more details.                                     *
*                                                                                                 *
* You should have received a copy of the GNU Lesser General Public                                *
* License along with HPMPC; if not, write to the Free Software                                    *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA                  *
*                                                                                                 *
* Author: Gianluca Frison, giaf (at) dtu.dk                                                       *
*                                                                                                 *
**************************************************************************************************/

void dgemm_ppp_nt_lib(int m, int n, int k, double *pA, int sda, double *pB, int sdb, double *pC, int sdc, int alg);
void dtrmm_ppp_lib(int m, int n, int offset, double *pA, int sda, double *pB, int sdb, double *pC, int sdc);
void dsyrk_ppp_lib(int n, int m, int k, double *pA, int sda, double *pC, int sdc);
void dpotrf_p_lib(int m, int n, double *pC, int sdc, int *info);
void dpotrf_p_dcopy_p_t_lib(int n, int nna, double *pC, int sdc, double *pL, int sdl, int *info);
void dgemv_p_n_lib(int n, int m, int offset, double *pA, int sda, double *x, double *y, int alg);
void dgemv_p_t_lib(int n, int m, int offset, double *pA, int sda, double *x, double *y, int alg);
void dtrmv_p_n_lib(int m, int offset, double *pA, int sda, double *x, double *y, int alg);
void dtrmv_p_t_lib(int m, int offset, double *pA, int sda, double *x, double *y, int alg);
void dsymv_p_lib(int m, int offset, double *pA, int sda, double *x, double *y, int alg);
void dmvmv_p_lib(int m, int n, int offset, double *pA, int sda, double *x_n, double *y_n, double *x_t, double *y_t, int alg);
void dtrsv_p_n_lib(int n, double *pA, int sda, double *x);
void dtrsv_p_t_lib(int n, double *pA, int sda, double *x);
