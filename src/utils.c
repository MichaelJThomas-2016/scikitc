//
// Created by Michael Thomas on 2/2/24.
//
#include <stdio.h>
#include "matrix.h"

void print_matrix(Matrix *matrix, const char *d_fmt) {
    int i, j;
    fprintf(stdout, "\n");
    for (i = 0; i < matrix->num_rows; ++i) {
        for (j = 0; j < matrix->num_cols; ++j) {
            fprintf(stdout, d_fmt, matrix->data[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}
