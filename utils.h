//
// Created by Michael Thomas on 2/2/24.
//

#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>

#define NP_CHECK(ptr) \
if (!(ptr)) { \
fprintf(stderr, "%s:%d NULL POINTER: %s n", \
__FILE__, __LINE__, (#ptr)); \
exit(-1); \
} \

// -----------------------------------------------------------------------------

// Enable this to allow debugging messages
#define DEBUG_TRUE 1

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

double scikitc_rand_interval(double min, double max);



int validate_matrix(unsigned int num_rows, unsigned int num_cols);
double rand_interval(double min, double max);
void quick_sort(double array[], int low, int high);
int partition(double array[], int low, int high);
void swap(double *a, double *b);
#endif //UTILS_H
