#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"

int main(int argc, char **argv) {

    srand(time(NULL));

    IntArray a = createIntArray(10); //размер массива

    for (int i = 0; i < a.length; ++i) {
        a.array[i] = rand() % 6; //разброс чисел
    }
    mergeSort(a);


    printArray(a);

    printf("%d\n",  binSearch(a, 1));
    printf("%d\n", naiveSearch(a, 1));
    printf("%d\n",  binSearchNR(a, 1));

    return 0;
}
