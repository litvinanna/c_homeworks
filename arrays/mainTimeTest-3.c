#include "array.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int sort_test(IntArray a) {
    for (int i = 1; i < a.length; ++i) {
        if (a.array[i] < a.array[i - 1]) return -1;
    }
    return 0;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int size = 1e4;
    int *array = (int *) calloc(size, sizeof(int));

    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }

    IntArray a = copy(array, size);
    free(array);

    //printArray(a);
    clock_t time_start = clock();
    quickSort(a);
    clock_t time_end = clock();
    //printArray(a);

    printf("%ld clocks.\n", time_end - time_start);
    printf("Sort test: %d\n", sort_test(a));

    time_start = clock();
    quickSort(a);
    time_end = clock();
    //printArray(a);

    printf("%ld sorted clocks.\n", time_end - time_start);

    deleteArray(a);
    return 0;
}
