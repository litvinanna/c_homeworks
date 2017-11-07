#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Missing file name\n");
        return 0;
    }

    char *fileName = argv[1];

    printf("File name: %s\n", fileName);

    FILE *file = fopen(fileName, "r");

    if (!file) {
        printf("File is not found\n");
        return 0;
    }

    int currentSize = 1;
    int *array = (int *) calloc(currentSize, sizeof(int));
    int count = 0;

    while (!feof(file)) {
        if (count >= currentSize) {
            array = realloc(array, currentSize * 2 * sizeof(int));
            currentSize *= 2;
        }

        int number;
        if (fscanf(file, "%d ", &number)) {
            array[count] = number;
            count += 1;
        }
    }

    IntArray a = copy(array, count);
    free(array);

    mergeSort(a);
    printArray(a);

    return 0;
}
