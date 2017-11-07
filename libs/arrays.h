#ifndef ARRAY_GUARD_H
#define ARRAY_GUARD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct {
    int length;
    int *array;
} IntArray;

IntArray createIntArray(int length);
IntArray copy(int *array, int length);
IntArray reversed(IntArray a);

typedef IntArray (* CreateFunctionInterface)(int length);

IntArray createNaturalIntArray(int length);
IntArray createRandomIntArray(int length);
IntArray createSortedIntArray(int length);
IntArray createAlmostSortedIntArray(int length);
IntArray createPartlySortedIntArray(int length);
IntArray createSligthlySpoiledIntArray(int length);

IntArray readFromStream(FILE * stream);
IntArray readFromFile (const char * filename);

void deleteArray(IntArray a);
IntArray merge(IntArray left, IntArray right);
void printArray(IntArray a);
IntArray concat(IntArray left, IntArray right);

typedef void (* SortFunctionInterface)(IntArray a);

void mergeSort(IntArray a);
void bubbleSort(IntArray a);
void quickSort(IntArray a);
void builtinQuickSort(IntArray a);
int testSort (IntArray a);

double checkSortTime(IntArray a, SortFunctionInterface f);

int binSearch(IntArray a, int key);
int naiveSearch(IntArray a, int key);
int binSearchNR(IntArray a, int key);

#endif // ARRAY_GURAD_H
