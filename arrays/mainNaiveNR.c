#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"

int comparator(const void *left,const void *right) {
    int a = *((int *) left);
    int b = *((int *) right);

    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

int main(int argc, char **argv) {

    srand(time(NULL));   // should only be called once
    //int r = rand();      // returns a pseudo-random integer between 0 and RAND_MAX

    IntArray a = createIntArray(25);
    //IntArray b = createIntArray(10);

    for (int i = 0; i < a.length; ++i) {
        a.array[i] = rand() % 5;
    }
    //qsort(a.array, a.length, sizeof(int), comparator);
    mergeSort(a);

    //for (int i = 0; i < b.length; ++i) {
    //    b.array[i] = rand() % 10;
    //}
    //qsort(b.array, b.length, sizeof(int), comparator);

    //IntArray r = merge(a, b);

    printArray(a);

    int s = binSearchNR(a, 1);
    printf("%d\n", s);
    printf("%d\n", naiveSearch(a, 1));


    deleteArray(a);
    return 0;
}


