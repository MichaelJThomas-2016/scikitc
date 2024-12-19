/**
Copyright 20201 Andrei N. Ciobanu

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef nml_UTIL
#define nml_UTIL

#include "utils.h"

#define NML_MIN_COEF 0.000000000000001

// *****************************************************************************
//
// Library structures
//
// *****************************************************************************
typedef struct matrix_s {
  unsigned int num_rows;
  unsigned int num_cols;
  double **data;
  int is_square;
} matrix;

typedef struct matrix_lup_s {
  matrix *L;
  matrix *U;
  matrix *P;
  unsigned int num_permutations;
} matrix_lup;

typedef struct matrix_qr_s {
  matrix *Q;
  matrix *R;
} matrix_qr;

// *****************************************************************************
//
// Constructing and destroying a matrix struct
//
// *****************************************************************************
matrix *matrix_new(unsigned int num_rows, unsigned int num_cols);
matrix *matrix_rnd(unsigned int num_rows, unsigned int num_cols, double min, double max);
matrix *matrix_sqr(unsigned int size);
matrix *matrix_sqr_rnd(unsigned int size, double min, double max);
matrix *matrix_eye(unsigned int size);
matrix *matrix_cp(matrix *m);
matrix *matrix_from(unsigned int num_rows, unsigned int num_cols, unsigned int n_vals, double *vals);
matrix *matrix_fromfile(const char *file);
matrix *matrix_fromfilef(FILE *f);
void matrix_free(matrix *matrix);

// *****************************************************************************
//
// Matrix Equality
//
// *****************************************************************************
int matrix_eqdim(matrix *m1, matrix *m2);
int matrix_eq(matrix *m1, matrix *m2, double tolerance);

// *****************************************************************************
//
// Matrix printing
//
// *****************************************************************************
void matrix_print(matrix *matrix);
void matrix_printf(matrix *matrix, const char *d_fmt);

// *****************************************************************************
//
// Accessing and modifying matrix elements
//
// *****************************************************************************
double matrix_get(matrix *matrix, unsigned int i, unsigned int j);
void matrix_set(matrix *matrix, unsigned int i, unsigned int j, double value);
matrix *matrix_col_get(matrix *m, unsigned int col);
matrix *matrix_col_mult(matrix *m, unsigned int col, double num);
int matrix_col_mult_r(matrix *m, unsigned int col, double num);
matrix *matrix_row_get(matrix *m, unsigned int row);
matrix *matrix_row_mult(matrix *m, unsigned int row, double num);
int matrix_row_mult_r(matrix *m, unsigned int row, double num);
void matrix_all_set(matrix *matrix, double value);
int matrix_diag_set(matrix *matrix, double value);
matrix *matrix_row_addrow(matrix *m, unsigned int where, unsigned int row, double multiplier);
int matrix_row_addrow_r(matrix *m, unsigned int where, unsigned int row, double multiplier);
matrix *matrix_smult(matrix *m, double num);
int matrix_smult_r(matrix *m, double num);

// *****************************************************************************
//
// Modifying the matrix structure
//
// *****************************************************************************
matrix *matrix_col_rem(matrix *m, unsigned int column);
matrix *matrix_row_rem(matrix *m, unsigned int row);
matrix *matrix_row_swap(matrix *m, unsigned int row1, unsigned int row2);
int matrix_row_swap_r(matrix *m, unsigned int row1, unsigned int row2);
matrix *matrix_col_swap(matrix *m, unsigned int col1, unsigned int col2);
int matrix_col_swap_r(matrix *m, unsigned int col1, unsigned int col2);
matrix *matrix_cath(unsigned int mnun, matrix **matrices);
matrix *matrix_catv(unsigned int mnum, matrix **matrices);

// *****************************************************************************
//
// Matrix Operations
//
// *****************************************************************************
matrix *matrix_add(matrix *m1, matrix *m2);
int matrix_add_r(matrix *m1, matrix *m2);
matrix *matrix_sub(matrix *m1, matrix *m2);
int matrix_sub_r(matrix *m1, matrix *m2);
matrix *matrix_dot(matrix *m1, matrix *m2);
matrix *matrix_transp(matrix *m);
double matrix_trace(matrix* m);

// *****************************************************************************
//
// Row Echelon
//
// *****************************************************************************
matrix *matrix_ref(matrix *m);
matrix *matrix_rref(matrix *m);

// *****************************************************************************
//
// LUP Decomposition
//
// *****************************************************************************

matrix_lup *matrix_lup_new(matrix *L, matrix *U, matrix *P, unsigned int num_permutations);
matrix_lup *matrix_lup_solve(matrix *m);
void matrix_lup_free(matrix_lup* lu);
void matrix_lup_print(matrix_lup *lu);
void matrix_lup_printf(matrix_lup *lu, const char *fmt);
double matrix_det(matrix_lup* lup);
matrix *matrix_lu_get(matrix_lup* lup);
matrix *matrix_inv(matrix_lup *m);

// *****************************************************************************
//
// Solving linear systems of equations
//
// *****************************************************************************

matrix *nml_ls_solvefwd(matrix *low_triang, matrix *b);
matrix *nml_ls_solvebck(matrix *upper_triang, matrix *b);
matrix *nml_ls_solve(matrix_lup *lup, matrix* b);

// *****************************************************************************
//
// QR Decomposition
//
// *****************************************************************************

double nml_vect_dot(matrix *m1, unsigned int m1col, matrix *m2, unsigned m2col);
matrix *matrix_l2norm(matrix *m);
double matrix_col_l2norm(matrix *m1, unsigned int j);
matrix *matrix_normalize(matrix *m);
int matrix_normalize_r(matrix *m);
matrix_qr *matrix_qr_new();
void matrix_qr_free(matrix_qr *qr);
matrix_qr * matrix_qr_solve(matrix *m);

#endif

#ifdef __cplusplus
}
#endif