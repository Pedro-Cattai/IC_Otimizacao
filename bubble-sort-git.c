#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort_parallel(int* array, int n) {
    int i, j, first;
    double start, end;

    start = omp_get_wtime();
    for(i = 0; i < n-1; i++) {
        first = i % 2; 

        #pragma omp parallel for default(none),shared(array,first,n)
        for(j=first; j < n-1; j += 2) {
            if(array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
    end = omp_get_wtime();
    
    printf("Time of parallel bubble sort: %f\n", end-start);
}

int main() {
    int n = 10000; // size of the array
    int* array = (int*) malloc(n * sizeof(int));

    // fill array with random integers
    for (int i = 0; i < n; i++) {
        array[i] = rand() % n;
    }

    bubble_sort_parallel(array, n);

    free(array);
    return 0;
}