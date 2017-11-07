#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Missing file name\n");
        return 0;
    }


   IntArray a = readFromFile(argv[1]);
    if (a.length == 0) {
        return 0;
    }

    quickSort(a);

    printArray(a);
    deleteArray(a);

    return 0;
}
