#include <stdio.h>
#include <math.h>



# include <stdlib.h>
#include "matrix.h"

// Shopuld there be a Vector struct???
double matrix_col_mean(Matrix *m, unsigned int col) {
    double sum = 0.0;
    int i;
    const  Matrix *col_vals = matrix_get_column(   m, col);
    for (i = 0; i < col_vals->num_rows; ++i) {
        sum += col_vals->data[i][0];
    }
    return sum / m->num_rows;

}
//
// double matrix_col_variance(Matrix *m, unsigned int col) {
//     double mu = matrix_col_mean(m,col);
//     double sum = 0.0;
//     int i;
//     for (i = 0; i < m[]->n; ++i) {
//         sum += pow(v->data[i] - mu, 2);
//     }
//     return sum / v->n;
// }

int main() {
    Matrix *vector = make_rand_matrix(20,1, 0, 100);
    printf("mean=%f\n", matrix_col_mean(vector, 3));
}