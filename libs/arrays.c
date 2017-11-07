#include "arrays.h"


IntArray createIntArray(int length) {
    IntArray a;

    a.length = length;
    a.array = (int *) calloc(length, sizeof(int));

    return a;
}

IntArray copy(int *array, int length) {
    IntArray a = createIntArray(length);
    for (int i = 0; i < length; ++i) {
        a.array[i] = array[i];
    }
    return a;
}


IntArray reversed(IntArray a) {
    int n = a.length;
    IntArray b = copy(a.array, n);
    for (int i = 0; i < n; i++) {
        a.array[i] = b.array[n - i - 1];
    }
    return b;
}


IntArray createNaturalIntArray(int length) {
    IntArray a = createIntArray(length);
    for (int i = 0; i < length; ++i) {
        a.array[i] = i + 1;
    }
    return a;
}

IntArray createRandomIntArray(int length) {
    IntArray a = createIntArray(length);

    for (int i = 0; i < length; i++) {
        a.array[i] = rand() % 100;
    }
    return a;

}

IntArray createSortedIntArray(int length) {
    IntArray a = createRandomIntArray(length);
    quickSort(a);
    return a;
}

IntArray createAlmostSortedIntArray(int length) {
    IntArray a = createSortedIntArray(length);
    int lucky = rand() % (length-1);
    a.array[lucky] += a.array[lucky+1];
    return a;
}

IntArray createPartlySortedIntArray(int length) {
    int size = length / 3;
    int res = length % 3;
    IntArray a = createSortedIntArray(size);
    IntArray b = createSortedIntArray(size);
    IntArray c = createSortedIntArray(size + res);
    IntArray ab = concat(a, b);
    IntArray abc = concat(ab, c);
    deleteArray(a);
    deleteArray(b);
    deleteArray(c);
    deleteArray(ab);
    return abc;
}

IntArray createSligthlySpoiledIntArray(int length) {
    IntArray a = createSortedIntArray(length);
    for (int i = 0; i < length - 3; i += 3) {
        int tmp = a.array[i];
        a.array[i] = a.array[i + 1];
        a.array[i + 1] = tmp;
    }
    return a;
}


IntArray readFromStream(FILE * stream) {
    int currentSize = 1;
    int *array = (int *) calloc(currentSize, sizeof(int));
    int count = 0;

    while (!feof(stream)) {
        if (count >= currentSize) {
            array = (int *) realloc(array, currentSize * 2 * sizeof(int));
            currentSize *= 2;
        }

        int number;
        if (fscanf(stream, "%d ", &number)) {
            array[count] = number;
            count += 1;
        }
    }

    IntArray a = copy(array, count);
    free(array);
    return a;
}

IntArray readFromFile (const char * fileName) {
    printf("File name: %s\n", fileName);

    FILE *file = fopen(fileName, "r");

    if (!file) {
        printf("File is not found\n");
        return createIntArray(0);
    }
    IntArray a = readFromStream (file);
    fclose(file);

    return a;
}

void deleteArray(IntArray a) {
    free(a.array);
}

void printArray(IntArray a) {
    for (int i = 0; i < a.length; ++i) {
        printf("%d ", a.array[i]);
    }
    printf("\n");
}

IntArray concat(IntArray left, IntArray right) {
    IntArray result = createIntArray(left.length + right.length);
    memcpy(result.array, left.array, left.length * sizeof(int));
    memcpy(result.array + left.length, right.array, right.length * sizeof(int));
    return result;
}

void append(IntArray x, IntArray result, int xArrayIndex, int resultArrayIndex) {
    while (xArrayIndex < x.length) {
        result.array[resultArrayIndex] = x.array[xArrayIndex];
        xArrayIndex += 1;
        resultArrayIndex += 1;
    }
}


IntArray merge(IntArray left, IntArray right) {
    IntArray result = createIntArray(left.length + right.length);

    int leftArrayIndex = 0, rightArrayIndex = 0, resultArrayIndex = 0;
    while (leftArrayIndex < left.length && rightArrayIndex < right.length) {
        int leftElement = left.array[leftArrayIndex];
        int rightElement = right.array[rightArrayIndex];
        if (leftElement <= rightElement) {
            result.array[resultArrayIndex] = leftElement;
            leftArrayIndex += 1;
        } else {
            result.array[resultArrayIndex] = rightElement;
            rightArrayIndex += 1;
        }
        resultArrayIndex += 1;
    }

    append(left, result, leftArrayIndex, resultArrayIndex);
    append(right, result, rightArrayIndex, resultArrayIndex);
    return result;
}



IntArray _mergeSort (IntArray a) {
    if (a.length == 1) return copy(a.array, 1);

    IntArray left;
    left.array = a.array;
    left.length = a.length / 2;

    IntArray right;
    right.array = a.array + left.length;
    right.length = a.length - left.length;

    IntArray sortedLeft = _mergeSort(left);
    IntArray sortedRight = _mergeSort(right);

    IntArray result = merge(sortedLeft, sortedRight);
    deleteArray(sortedLeft);
    deleteArray(sortedRight);
    return result;
}

void mergeSort(IntArray a) {
    IntArray b = _mergeSort(a);
    for (int i = 0; i < a.length; ++i) {
        a.array[i] = b.array[i];
    }
    deleteArray(b);
}

void bubbleSort(IntArray a) {
    for (int j = 1; j < a.length; j++) {
        for(int i = 1; i < a.length - j + 1; i++) {
            if (a.array[i] < a.array[i-1]) {
                int tmp = a.array[i];
                a.array[i] = a.array[i-1];
                a.array[i-1] = tmp;
            }
        }
    }
}

void quickSort(IntArray a) {
    if (a.length <= 8) {
        bubbleSort(a);
        return;
    }

    //printf("%d\n", a.length);
    int pivotIndex = rand() % a.length;
    int pivot = a.array[pivotIndex];
    a.array[pivotIndex] = a.array[0];
    a.array[0] = pivot;
    int i = 0;
    int j = a.length - 1;
    int direction = 0;

    while (i != j) {
        switch (direction) {
        case 0:
            if (a.array[j] < pivot) {
                a.array[i] = a.array[j];
                a.array[j] = pivot;
                i += 1;
                direction = 1;
            } else {
                j -= 1;
            }
            break;
        case 1:
            if (a.array[i] > pivot) {
                a.array[j] = a.array[i];
                a.array[i] = pivot;
                j -= 1;
                direction = 0;
            } else {
                i += 1;
            }
            break;
        }
        // printf("%d %d   ::: ", i, j);
        // printArray(a);
    }

    IntArray left;
    left.array = a.array;
    left.length = i;
    quickSort(left);


    IntArray right;
    right.array = a.array + j + 1;
    right.length = a.length - i - 1;
    quickSort(right);
}

int ascending_comparator(const void *a, const void *b) {
    const int ia = *((const int *) a);
    const int ib = *((const int *) b);

    if (ia > ib) return 1;
    if (ia < ib) return -1;
    return 0;
}

void builtinQuickSort(IntArray a) {
    qsort(a.array, a.length, sizeof(int), ascending_comparator);
}

int testSort(IntArray a) {
    for (int i = 1; i < a.length; ++i) {
        if (a.array[i] < a.array[i - 1]) return -1;
    }
    return 0;
}

double checkSortTime(IntArray a, SortFunctionInterface f) {
    IntArray c = copy(a.array, a.length);

    clock_t start = clock();
    f(c);
    clock_t end = clock();
    if (testSort(c) != 0) {
        return -1.0;
    }
    deleteArray(c);
    return (double) (end - start) / CLOCKS_PER_SEC;
}


int _binSearch(IntArray a, int key, int start, int end) {
    //printf("%d ", start);
    //printf("%d\n", end);
    if (end  <= start){
        return -1;
    }

    int middle = (end + start) / 2;

    // printf("%d\n", middle);
    int midelement = a.array[middle];
    if (midelement == key){
        return middle;
    }
    if (midelement > key) {
        return _binSearch(a, key, start, middle);
    } else {
        return _binSearch(a, key, middle + 1, end);
    }
}

int binSearch(IntArray a, int key) {
    int index = _binSearch(a, key, 0, a.length);
    while (index > 0 && a.array[index - 1] == key) {
        index -= 1;
    }
    return index;
}


int naiveSearch(IntArray a, int key) {
    for (int i = 0; i < a.length; ++i) {
        if (a.array[i] == key){
            return i;
        }
    }
    return -1;
}


int _binSearchNR(IntArray a, int key) {
    int start = 0, end = a.length;
    while(start < end){
        int middle = (end + start) / 2;
        int midelement = a.array[middle];
        if (midelement == key){
            return middle;
        }
        if (midelement > key) {
            end = middle;
        } else {
            start = middle + 1;
        }
    }
    return -1;
}

int binSearchNR (IntArray a, int key){
    int index = _binSearchNR(a, key);
    while (index > 0 && a.array[index - 1] == key) {
        index -= 1;
    }
    return index;
}




