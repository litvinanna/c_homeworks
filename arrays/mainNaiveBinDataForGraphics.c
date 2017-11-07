#include "array.h"
#include <sys/time.h>

double Timer() {
    double t1;
    struct timeval time;
    gettimeofday(&(time), NULL);
    t1 =  (double)time.tv_sec + (double)time.tv_usec/(1000.0*1000.0);
    return t1;
}

int main(int argc, char **argv) {
     if (argc < 2) {
        printf("Missing file name\n");
        return 0;
    }

    char *fileName = argv[1];

    printf("File name: %s\n", fileName);

    FILE *file = fopen(fileName, "w");

    if (!file) {
        printf("File is not found\n");
        return 0;
    }


    srand(time(NULL));

    int size = 2;
    clock_t timeBin = 0;
    clock_t timeNaive = 0;
    clock_t timeSort = 0;
    clock_t time_start;
    clock_t time_end;

    //printf("%ld\n", CLOCKS_PER_SEC);

    while (size <= 100000000) {
        IntArray a = createRandomIntArray(size);

        time_start = clock();
	    quickSort(a);
	    time_end = clock();
	    timeSort = (time_end - time_start);

	    int keyIndex = size - 1;
        //int keyIndex = 0;
        int key = a.array[keyIndex];

        time_start = clock();
        int index1 = naiveSearch(a, key);
	    int key1 = a.array[index1];
        time_end = clock();
        timeNaive = (time_end - time_start);

        //printArray(a);
        int binIndex;
        int binKey;
        timeBin = 0;
        for (int i = 0; i < 10000; ++i) {
            time_start = clock();
            binIndex = binSearchNR(a, key);
            binKey = a.array[binIndex];
            time_end = clock();
            timeBin += (time_end - time_start);
        }

        fprintf(file, "%10d\t%.6f\t%.6f\t%.10f\n", size, (double)timeSort/CLOCKS_PER_SEC, (double)timeNaive/CLOCKS_PER_SEC, ((double)timeBin/10000) / CLOCKS_PER_SEC);
        size *= 2;
        deleteArray(a);
    }

    fclose(file);
    return 0;
}
