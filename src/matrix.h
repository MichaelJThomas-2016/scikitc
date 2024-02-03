//
// Created by Michael Thomas on 2/2/24.
//

#ifndef MATRIX_H
#define MATRIX_H
#define RE_MIN_COEF = 0.000000000000001

#define NP_CHECK(ptr) \
if (!(ptr)) { \
fprintf(stderr, "%s:%d NULL POINTER: %s n", \
__FILE__, __LINE__, (#ptr)); \
exit(-1); \
}

// *****************************************************************************
//
// Library structures
//
// *****************************************************************************

typedef struct Matrix {
    int num_rows;
    int num_cols;
    // ND array tjat stores data in rows and colms
    double **data;
    // Bool that determines if the matrix is `square` N == M
    int is_square;
} Matrix;

double rand_interval(double min, double max);

// *****************************************************************************
//
// Constructing and destroying a matrix struct
//
// *****************************************************************************

Matrix *make_matrix(unsigned int num_rows, unsigned int num_cols);
int validate_matrix(unsigned int num_rows, unsigned int num_cols);
Matrix *make_rand_matrix(unsigned int num_rows, unsigned int num_cols, double min, double max);
Matrix *make_square_matrix(unsigned int size);
Matrix *matrix_cp(Matrix *m);
Matrix *make_eye_matrix(unsigned int size);
Matrix *make_square_rand_matrix(unsigned int size, double min, double max);
Matrix *matrix_from_file(FILE *f);
void free_matrix(Matrix *matrix);


// *****************************************************************************
//
// Matrix Equality
//
// *****************************************************************************
int matrix_eqdim(Matrix *m1, Matrix *m2);
int matrix_eq(Matrix *m1, Matrix *m2,double tolerance);


// *****************************************************************************
//
// Matrix printing
//
// *****************************************************************************
void print_matrix(Matrix *matrix, const char *d_fmt);




// *****************************************************************************
//
// Matrix Operations
//
// *****************************************************************************
Matrix *matrix_add(Matrix *m1, Matrix *m2);
Matrix *matrix_sub(Matrix *m1, Matrix *m2);
Matrix *matrix_row_scalar_mult(Matrix *m, unsigned int row, double scalar);
Matrix *matrix_get_row(Matrix *m, unsigned int row);
Matrix *matrix_get_column(Matrix *m, unsigned int col);
void matrix_set_all(Matrix *m, double val);
int matrix_set_diagonal(Matrix *m, double val);
int matrix_row_scalar_mult_r(Matrix *m, unsigned int row, double scalar);
Matrix *matrix_row_scalar_mult(Matrix *m, unsigned int row, double num);
int matrix_column_scalar_mult_r(Matrix *m, unsigned int col, double scalar);
Matrix *matrix_column_scalar_mult(Matrix *m, unsigned int col, double num);
int matrix_add_row_r(Matrix *m, unsigned int where, unsigned int row, double multiplier);
Matrix *matrix_add_row(Matrix *m, unsigned int where, unsigned int col, double multiplier);
int matrix_mult_scalar_r(Matrix *m, double scalar);
Matrix *matrix_mult_scalar(Matrix *m, double scalar);
Matrix *matrix_drop_column(Matrix *m, unsigned int col);
Matrix *matrix_drop_row(Matrix *m, unsigned int row);
int matrix_swap_row_r(Matrix *m, unsigned int row1, unsigned int row2);
Matrix *maxrtix_swap_row(Matrix *m, unsigned int row1, unsigned int row2);
int matrix_swap_column_r(Matrix *m, unsigned int col1, unsigned int col2);
Matrix *matrix_swap_column(Matrix *m, unsigned int col1, unsigned int col2);
Matrix *matrix_concatenate_horizontal(unsigned int mnum, Matrix **matricies);
Matrix *matrix_concate_vertical(unsigned int mnum, Matrix **matricies);
int matrix_sub_r(Matrix *m1, Matrix *m2);
Matrix *matrix_dot(Matrix *m1, Matrix *m2);
#endif //MATRIX_H
