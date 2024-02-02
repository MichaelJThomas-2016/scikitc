#include "util.h"
#include <stdlib.h>

int validate_matrix(unsigned int num_rows, unsigned int num_cols) {
    if (num_cols > 0 && num_rows > 0) {
        return 1;
    }
    return 0;
};

#define	RAND_MAX	0x7fffffff
double rand_interval(double min, double max) {
    double d;
    d = (double) rand() / ((double) RAND_MAX + 1);
    return (min + d * (max - min));
}


// function to swap elements
void swap(double *a, double *b) {
    double t = *a;
    *a = *b;
    *b = t;
}

// function to find the partition position
int partition(double array[], int low, int high) {

    // select the rightmost element as pivot
    int pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

void quick_sort(double array[], int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quick_sort(array, low, pi - 1);

        // recursive call on the right of pivot
        quick_sort(array, pi + 1, high);
    }
}
//
// Created by Michael Thomas on 2/2/24.
//
