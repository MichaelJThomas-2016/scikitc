#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "matrix.h"



#define CANNOT_ADD_TO_ROW "Cannot add row %d to row %d. Matrix has only %d rows"
#define CANNOT_REMOVE_COLUMN "Cannot remove column %d. Matrix has only %d columns"
#define CANNOT_REMOVE_ROW "Cannot remove row %d. Matrix has only %d rows"
#define CANNOT_SWAP_ROWS "Cannot swap rows %d and %d. Matrix has only %d rows"
#define CANNOT_SWAP_COLUMNS "Cannot swap columns %d and %d. Matrix has only %d columns"
#define CANNOT_CONCATENATE_H "Cannot concatenate matrices horizontally. Matrices have different number of rows"
#define CANNOT_CONCATENATE_V "Cannot concatenate matrices vertically. Matrices have different number of columns"
#define CANNOT_MULITPLY "Cannot multiply matrices. Number of columns in the first matrix does not match the number of rows in the second matrix"
#define CANNOT_ADD "Cannot add matrices. Matrices have different dimensions"
#define CANNOT_SUBTRACT "Cannot subtract matrices. Matrices have different dimensions"
#define INCONSITENT_ARRAY "Inconsistent array. Matrix %d is NULL. Array has %d elements"


// Prints the matrix on the stdout (with a custom formatting for elements)


int validate_matrix(unsigned int num_rows, unsigned int num_cols) {
    if (num_cols > 0 && num_rows > 0) {
        return 1;
    }
    return 0;
};

double rand_interval(double min, double max) {
    double d;
    d = (double) rand() / ((double) RAND_MAX + 1);
    return (min + d * (max - min));
}

// Constructor-like
// Allocates memory for a new matrix
// All elements in the matrix are 0.0
Matrix *make_matrix(unsigned int num_rows, unsigned int num_cols) {
    int valid = validate_matrix(num_rows, num_cols);
    if (valid) {
        Matrix *m = calloc(1, sizeof(*m));
        NP_CHECK(m);
        m->num_rows = num_rows;
        m->num_cols = num_cols;
        m->is_square = num_rows == num_cols;
        m->data = calloc(num_rows, sizeof(*m->data));
        NP_CHECK(m->data);
        int i;
        for (i = 0; i < num_rows; i++) {
            m->data[i] = calloc(m->num_cols, sizeof(**m->data));
            NP_CHECK(m->data[i]);
        }
        return m;
    }
    return NULL;
}

void free_matrix(Matrix *matrix) {
    int i;
    for (i = 0; i < matrix->num_rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// Dynamically allocates a new Matrix
// Initialise the matrix by copying another one
Matrix *matrix_cp(Matrix *m) {
    Matrix *r = make_matrix(m->num_rows, m->num_cols);
    int i, j;
    for (i = 0; i < r->num_rows; i++) {
        for (j = 0; j < r->num_cols; j++) {
            r->data[i][j] = m->data[i][j];
        }
    }
    return r;
}

Matrix *make_rand_matrix(unsigned int num_rows, unsigned int num_cols, double min, double max) {
    const int valid = validate_matrix(num_rows, num_cols);
    if (valid) {
        Matrix *r = make_matrix(num_rows, num_cols);
        int i, j;
        for (i = 0; i < num_rows; i++) {
            for (j = 0; j < num_cols; j++) {
                r->data[i][j] = rand_interval(min, max);
            }
        }
        return r;
    }
    return NULL;
};

Matrix *make_square_matrix(unsigned int size) {
    return make_matrix(size, size);
}

Matrix *make_square_rand_matrix(unsigned int size, double min, double max) {
    return make_rand_matrix(size, size, min, max);
}


Matrix *make_eye_matrix(unsigned int size) {
    // Make an identity matrix - A square matrix with 1's on the first diagonal
    // and 0's everywhere else
    Matrix *m = make_square_matrix(size);
    int i;
    for (i = 0; i < size; i++) {
        m->data[i][i] = 1.0;
    }
    return m;
}

Matrix *matrix_from_file(FILE *f) {
    int i, j;
    unsigned int num_rows = 0, num_cols = 0;
    fscanf(f, "%d", &num_rows);
    fscanf(f, "%d", &num_cols);
    Matrix *m = make_matrix(num_rows, num_cols);
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            fscanf(f, "%lf\t", &m->data[i][j]);
        }
    }
    return m;
}

// Check if 2 matricies have equal dimensions
int matrix_eqdim(Matrix *m1, Matrix *m2) {
    return (m1->num_rows == m2->num_rows) && (m1->num_cols == m2->num_cols);
}

// Checks if two matrices have the same dimensions, and the elements
// are all equal to each other with a given tolerance;
// For exact equality use tolerance = 0.0
int matrix_eq(Matrix *m1, Matrix *m2, double tolerance) {
    if (!matrix_eqdim(m1, m2)) {
        return 0;
    }
    int i, j;
    for (i = 0; i < m1->num_rows; i++) {
        for (j = 0; j < m1->num_cols; j++) {
            if (fabs(m1->data[i][j] - m2->data[i][j]) > tolerance) {
                return 0;
            }
        }
    }
    return 1;
}

Matrix *matrix_get_column(Matrix *m, unsigned int col) {
    if (col >= m->num_cols) {
        return NULL;
    }
    Matrix *r = make_matrix(m->num_rows, 1);
    int i;
    for (i = 0; i < m->num_rows; i++) {
        r->data[i][0] = m->data[i][col];
    }
    return r;
}

Matrix *matrix_get_row(Matrix *m, unsigned int row) {
    if (row >= m->num_rows) {
        return NULL;
    }
    Matrix *r = make_matrix(1, m->num_cols);

    memcpy(r->data[0], m->data[row], m->num_cols * sizeof(*r ->data[0]));
    return r;
}

void matrix_set_all(Matrix *m, double value) {
    int i, j;
    for (i = 0; i < m->num_rows; i++) {
        for (j = 0; j < m->num_cols; j++) {
            m->data[i][j] = value;
        }
    }
}

int matrix_set_diagonal(Matrix *m, double value) {
    if (!m->is_square) {
        return 0;
    }
    int i;
    for (i = 0; i < m->num_rows; i++) {
        m->data[i][i] = value;
    }
    return 1;
}


int matrix_row_scalar_mult_r(Matrix *m, unsigned int row, double num) {
    if (row >= m->num_rows) {
        return 0;
    }
    int i;
    for (i = 0; i < m->num_cols; i++) {
        m->data[row][i] *= num;
    }
    return 1;
}

/*
matrix_row_scalar_mult([1,2,3] 0, 2) = [2,4,6]
                       [4,5,6]         [4,5,6]
*/
Matrix *matrix_row_scalar_mult(Matrix *m, unsigned int row, double num) {
    Matrix *r = matrix_cp(m);
    if (!matrix_row_scalar_mult_r(r, row, num)) {
        free_matrix(r);
        return NULL;
    }
    return r;
}

int matrix_column_scalar_mult_r(Matrix *m, unsigned int col, double num) {
    if (col >= m->num_cols) {
        return 0;
    }
    int i;
    for (i = 0; i < m->num_rows; i++) {
        m->data[i][col] *= num;
    }
    return 1;
}

/*
matrix_column_scalar_mult([1,2,3] 0, 2) = [2,2,3]
                          [4,5,6]         [8,5,6]
*/
Matrix *matrix_column_scalar_mult(Matrix *m, unsigned int col, double num) {
    Matrix *r = matrix_cp(m);
    if (!matrix_column_scalar_mult_r(r, col, num)) {
        free_matrix(r);
        return NULL;
    }
    return r;
}


int matrix_add_row_r(Matrix *m, unsigned int where, unsigned int row, double multiplier) {
    if (where >= m->num_rows || row >= m->num_rows  ) {

        return 0;
    }
    int i;
    for (i = 0; i < m->num_cols; i++) {
        m->data[where][i] += m->data[row][i] * multiplier;
    }
    return 1;
}

/*

 Multiplier could be used for decpmposition and row echelon form
matrix_add_row([1,2,3] 0, 1, 1.0) = [5,7,9]
               [4,5,6]              [4,5,6]
               [7,8,9]              [7,8,9]
*/
Matrix *matrix_add_row(Matrix *m, unsigned int where, unsigned int row, double multiplier) {
    Matrix *r = matrix_cp(m);
    if (!matrix_add_row_r(r, where, row, multiplier)) {
        free_matrix(r);
        return NULL;
    }
    return r;
}

int matrix_mult_scalar_r(Matrix *m, double num) {
    int i, j;
    for (i = 0; i < m->num_rows; i++) {
        for (j = 0; j < m->num_cols; j++) {
            m->data[i][j] *= num;
        }
    }
    return 1;
}

/*
matrix_mult_scalar([1,2,3] 2) = [2,4,6]
                   [4,5,6]       [8,10,12]
                   [7,8,9]       [14,16,18]
*/
Matrix *matrix_mult_scalar(Matrix *m, double num) {
    Matrix *r = matrix_cp(m);
    matrix_mult_scalar_r(r, num);
    return r;
}

// Drop a column from a matrix
Matrix *matrix_drop_column(Matrix *m, unsigned int column) {
    if (column >= m->num_cols) {

        return NULL;
    }
    Matrix *r = make_matrix(m->num_rows, m->num_cols - 1);
    int i, j, k;
    for (i = 0; i < m->num_rows; i++) {
        for (j = 0; j < m->num_cols; j++) {
            if (column != j) {
                r->data[i][k++] = m->data[i][j];
            }
        }
    }
    return r;
}

// Drop a row from a matrix
Matrix *matrix_drop_row(Matrix *m, unsigned int row) {
    if (row >= m->num_rows) {

        return NULL;
    }
    Matrix *r = make_matrix(m->num_rows - 1, m->num_cols);
    int i, j, k;
    for (i = 0, k = 0; i < m->num_rows; i++) {
        if (row != i) {
            for (j = 0; j < m->num_cols; j++) {
                r->data[k][j] = m->data[i][j];
            }
            k++;
        }
    }
    return r;
}

// Modifies the existing matrix m, by swapping the two rows row1 and row2
int matrix_swap_row_r(Matrix *m, unsigned int row1, unsigned int row2) {
    if (row1 >= m->num_rows || row2 >= m->num_rows) {

        return 0;
    }
    double *tmp = m->data[row1];
    m->data[row1] = m->data[row2];
    m->data[row2] = tmp;
    return 1;
}

/*
matrix_swap_row([1,2,3] 0, 1) = [4,5,6]
                [4,5,6],        [1,2,3]
                [7,8,9]         [7,8,9]
*/
Matrix *maxrtix_swap_row(Matrix *m, unsigned int row1, unsigned int row2) {
    Matrix *r = matrix_cp(m);
    if (!matrix_swap_row_r(r, row1, row2)) {
        free_matrix(r);
        return NULL;
    }
    return r;
}

int matrix_swap_column_r(Matrix *m, unsigned int col1, unsigned int col2) {
    if (col1 >= m->num_cols || col2 >= m->num_cols) {

        return 0;
    }
    int i;
    for (i = 0; i < m->num_rows; i++) {
        double tmp = m->data[i][col1];
        m->data[i][col1] = m->data[i][col2];
        m->data[i][col2] = tmp;
    }
    return 1;
}

/*
matrix_swap_column([1,2,3] 0, 1) = [2,1,3]
                   [4,5,6],        [5,4,6]
 */
Matrix *matrix_swap_column(Matrix *m, unsigned int col1, unsigned int col2) {
    Matrix *r = matrix_cp(m);
    if (!matrix_swap_column_r(r, col1, col2)) {
        free_matrix(r);
        return NULL;
    }
    return r;
}

// takes a variable number of matrices (matricies**)
// and returns a new matrix that represents the horizontal concatenation of those matrices.
/*
    A = [1 2 3]
        [4 5 6]
    B = [4,0,9]
    C = [7,8,9]
        [11,12,13]

    matrix_concatenate_horizontal(a,b,c) ->
        [1,2,3]
        [4,5,6]
        [4,0,9]
        [7,8,9]
        [11,12,13]
*/

Matrix *matrix_concatenate_horizontal(unsigned int mnum, Matrix **matricies) {
    // We just return the one matrix supplied as the first param
    // no need for additional logic
    if (1 == mnum) {
        return matrix_cp(matricies[0]);
    }
    // Calc. total number of columns to know how to allocate memory
    // for the resulting matrix
    //i, j are used to iterate over the resulting matrix (r);
    //k is the index of the current we are concatenating;
    //offset is used to determine we need to jump to next matrix that needs concatenation.
    int i, j, k, offset;
    unsigned int lrow, ncols;
    lrow = matricies[0]->num_rows;
    ncols = matricies[0]->num_cols;
    for (k = 1; k < mnum; k++) {
        if (NULL == matricies[k]) {
            return NULL;
        }
        if (lrow != matricies[k]->num_rows) {

            return NULL;
        }
        ncols += matricies[k]->num_cols;
    }
    // At this point we know how the resulting matrix looks like,
    // we allocate memory for it accordingly
    Matrix *r = make_matrix(lrow, ncols);
    for (i = 0; i < r->num_rows; i++) {
        k = 0;
        offset = 0;
        for (j = 0; j < r->num_cols; j++) {
            // If the column index of marr[k] overflows
            if (j - offset == matricies[k]->num_cols) {
                offset += matricies[k]->num_cols;
                // We jump to the next matrix in the array
                k++;
            }
        }
        r->data[i][j] = matricies[k]->data[i][j - offset];
    }
    return r;
}

/*
    A = [1,2,3]
        [4,5,6]
    B = [4,0,9]
        [7,8,9]

matrix_concate_vertical(a,b) ->
    [1,2,3,4,0,9]
    [4,5,6,7,8,9]
*/
Matrix *matrix_concate_vertical(unsigned int mnum, Matrix **marr) {
    if (0 == mnum) {
        return NULL;
    }
    if (1 == mnum) {
        return matrix_cp(marr[0]);
    }

    // We check to see if the matrices have the same number of columns
    int lcol, i, j, k, offset;
    unsigned int numrows;
    Matrix *r;
    lcol = marr[0]->num_cols;
    numrows = 0;
    for (i = 0; i < mnum; i++) {
        if (NULL == marr[i]) {
            return NULL;
        }
        if (lcol != marr[i]->num_cols) {
            return NULL;
        }
        // In the same time we calculate the resulting matrix number of rows
        numrows += marr[i]->num_rows;
    }
    // At this point we know the dimensions of the resulting Matrix
    r = make_matrix(numrows, lcol);
    // We start copying the values one by one
    for (j = 0; j < r->num_cols; j++) {
        offset = 0;
        k = 0;
        for (i = 0; i < r->num_rows; i++) {
            if (i - offset == marr[k]->num_rows) {
                offset += marr[k]->num_rows;
                k++;
            }
            r->data[i][j] = marr[k]->data[i - offset][j];
        }
    }
    return r;
}

int matrix_add_r(Matrix *m1, Matrix *m2) {
    if (!matrix_eqdim(m1, m2)) {
        return 0;
    }
    int i, j;
    for (i = 0; i < m1->num_rows; i++) {
        for (j = 0; j < m1->num_cols; j++) {
            m1->data[i][j] += m2->data[i][j];
        }
    }
    return 1;
}

/*
matrix_add([1,2,3] [4,5,6]) = [5,7,9]
           [4,5,6] [7,8,9]    [11,13,15]
 */
Matrix *matrix_add(Matrix *m1, Matrix *m2) {
    Matrix *r = matrix_cp(m1);
    if (!matrix_add_r(r, m2)) {
        free_matrix(r);
        return NULL;
    }
    return r;
}


int matrix_sub_r(Matrix *m1, Matrix *m2) {
    if (!matrix_eqdim(m1, m2)) {
        return 0;
    }
    int i, j;
    for (i = 0; i < m1->num_rows; i++) {
        for (j = 0; j < m1->num_cols; j++) {
            m1->data[i][j] -= m2->data[i][j];
        }
    }
    return 1;
}

/*
matrix_sub([1,2,3] [4,5,6]) = [-3,-3,-3]
           [4,5,6] [7,8,9]    [-3,-3,-3]
*/
Matrix *matrix_sub(Matrix *m1, Matrix *m2) {
    Matrix *r = matrix_cp(m1);
    if (!matrix_sub_r(r, m2)) {
        free_matrix(r);
        return NULL;
    }
    return r;
}

/*
    A = [1,2,3]
        [4,5,6]
    B = [4,0,9]
        [7,8,9]
    matrix_dot(A,B) ->
        [1*4+2*7+3*9, 1*0+2*8+3*9, 1*9+2*9+3*9]
        [4*4+5*7+6*9, 4*0+5*8+6*9, 4*9+5*9+6*9]
    ******************************************************
    C  = [35, 34, 45]
         [80, 79, 99]
    D = [1, 3
         2, 4
         3, 5]
    matrix_dot(C,D) ->
        [35*1 + 34*2 + 45*3, 35*3 + 34*4 + 45*5]
        [80*1 + 79*2 + 99*3, 80*3 + 79*4 + 99*5]

The product
A * B is defined if and only if the number of columns in A equals the number of rows in B, which is n.
The resulting product matrix will then “inherit” the number of rows from A and the number of columns from B
*/

Matrix *matrix_dot(Matrix *m1, Matrix *m2) {
    if (m1->num_cols != m2->num_rows) {
        return 0;
    }
    int i, j, k;
    Matrix *r = make_matrix(m1->num_rows, m2->num_cols);
    for (i = 0; i < m1->num_rows; i++) {
        for (j = 0; j < m2->num_cols; j++) {
            for (k = 0; k < m1->num_cols; k++) {
                r->data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }
    return r;
}
//
// Created by Michael Thomas on 2/2/24.
//
