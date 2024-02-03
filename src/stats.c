#include <stdio.h>
#include <math.h>


# include <stdlib.h>
#include "matrix.c"

// Shopuld there be a Vector struct???
double matrix_col_mean_r(Matrix *m) {
    double sum = 0.0;
    int i;
    for (i = 0; i < m->num_rows; ++i) {
        sum += m->data[i][0];
    }
    return sum / m->num_rows;
}
double matrix_col_mean(Matrix *m, unsigned int col) {
    return matrix_col_mean_r(matrix_get_column(m, col));

}

double matrix_col_variance(Matrix *m, unsigned int col) {
    double mu = matrix_col_mean(m,col);
    double sum = 0.0;
    int i;
    for (i = 0; i < m->num_rows; ++i) {
        sum += pow(*m->data[i] - mu, 2);
    }
    return sum / m->num_rows;
}

double matrix_col_stddev(Matrix *m, unsigned int col) {
    return sqrt(matrix_col_variance(m, col));
}

