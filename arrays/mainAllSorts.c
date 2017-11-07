#include "array.h"
#include <time.h>


int main(int argc, char **argv) {
    srand(time(NULL));
    IntArray a = createRandomIntArray (1000);

    IntArray b = copy(a.array, a.length);
    clock_t time_start = clock();
    quickSort(b);
    clock_t time_end = clock();

    printf("quickSort: %f seconds\n", (double)(time_end - time_start) / CLOCKS_PER_SEC);
    printf("Sort test: %d\n", testSort(b));

    deleteArray(b);

    b = copy(a.array, a.length);
    time_start = clock();
    mergeSort(b);
    time_end = clock();

    printf("mergeSort: %f seconds\n", (double)(time_end - time_start) / CLOCKS_PER_SEC);
    printf("Sort test: %d\n", testSort(b));

    deleteArray(b);

    b = copy(a.array, a.length);
    time_start = clock();
    bubbleSort(b);
    time_end = clock();

    printf("bubbleSort:%f seconds\n", (double)(time_end - time_start) / CLOCKS_PER_SEC);
    printf("Sort test: %d\n", testSort(b));

    //printArray(b);
    deleteArray(b);


    return 0;
}

