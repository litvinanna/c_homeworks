#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "array.h"

int main(int argc, char **argv) {
    if (argc < 5) {
        printf("program <leftRange> <rightRange> <array type> <sort algorithm>\n\n");

        printf("  leftRange: integer\n");
        printf("  rightRange: integer\n\n");

        printf("  array type:\n");
        printf("    1 - all (ascending)\n");
        printf("    2 - random\n");
        printf("    3 - sorted\n");
        printf("    4 - almost sorted\n");
        printf("    5 - slightly spoiled\n");
        printf("    6 - partly sorted\n");
        printf("  *-1 - reversed\n");

        printf("\n");
        printf("  sort algorithm\n");
        printf("    0 - all\n");
        printf("    1 - bubble\n");
        printf("    2 - merge\n");
        printf("    3 - quick\n");
        printf("    4 - built-in-quick\n");
        return 0;
    }

    int leftRange = atoi(argv[1]);
    int rightRange = atoi(argv[2]);
    int arrayTypeSigned = atoi(argv[3]);
    int arrayType = fabs(arrayTypeSigned);
    int sortAlgorithm = atoi(argv[4]);

    if((arrayType == 0 || arrayType == 1 ||arrayType==-1) && sortAlgorithm == 0){
        printf("Cannot display 3d table :( \n");
        return 0;
    }

    const char *sortNames[] = {"bubble", "merge", "quick", "blt-in-q" };
    const SortFunctionInterface sorters[] = {bubbleSort, mergeSort, quickSort, builtinQuickSort };


    const char *arrayNames[] = {"random", "sorted", "almost sorted", "slightly spoiled", "partly sorted",
        "reverse random", "reverse sorted", "reverse almost sorted", "reverse slightly spoiled", "reverse partly sorted" };

    const CreateFunctionInterface creators[] = {
        createRandomIntArray,
        createSortedIntArray,
        createAlmostSortedIntArray,
        createSligthlySpoiledIntArray,
        createPartlySortedIntArray
        };


    if (sortAlgorithm == 0) {
        printf("#array type: %s\n", arrayNames[arrayType-2]);
        printf("#%7s", "size");
        for (int i =0 ; i < 4; ++i) {
            printf("%10s", sortNames[i]);
        }
        printf("\n");
        for (int size = leftRange; size <= rightRange; size *= 2) {
            IntArray a = creators[arrayType-2](size);
            printf("%8d", size);
            for (int i = 0; i < 4; ++i) {
                IntArray b = copy(a.array, a.length);
                printf("%10f", checkSortTime(b, sorters[i]));
                deleteArray(b);
            }
            deleteArray(a);
            printf("\n");
        }

    }


    else if (arrayType == 1) {
            printf("#sort algorithms: %s\n", sortNames[sortAlgorithm-1]);
            if (arrayTypeSigned < 0) {
                printf("#All array types are reversed\n");
            }
            printf("#%7s", "size");
            for (int i =0 ; i < 5; ++i) {
                printf("%17s", arrayNames[i]);
            }
            printf("\n");
            for (int size = leftRange; size <= rightRange; size *= 2) {
                printf("%8d", size);
                for (int creatorIndex = 0; creatorIndex < 5; ++creatorIndex) {
                    IntArray a = creators[creatorIndex](size);
                    if (arrayTypeSigned < 0) {
                        a = reversed(a);
                    }
                    printf("%17f", checkSortTime(a, sorters[sortAlgorithm-1]));
                    deleteArray(a);
                }
                printf("\n");
            }

    } else {
        printf("#array type: %s\n", arrayNames[arrayType-2]);
        printf("#%7s%10s\n", "size", sortNames[sortAlgorithm-1]);
        for (int size = leftRange; size <= rightRange; size *= 2) {
            IntArray a = creators[arrayType-2](size);
            printf("%8d   %8f\n", size, checkSortTime(a, sorters[sortAlgorithm-1]));
            deleteArray(a);
        }
    }

    return 0;
}
