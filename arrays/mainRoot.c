#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include <math.h>

int error_precision(double error) {
    error = fabs(error);
    double decimal;
    double frac = modf(error, &decimal);

    if (fabs(decimal) > 0.0) {
        return 0;
    }

    int precision = 0;

    while (frac < 1.0) {
        frac *= 10;
        precision += 1;
        if (precision > 100) break;
    }

    return precision;
}



int main(int argc, char **argv) {
    int precision = 10;
    int number = 2;
    if (argc < 3){
        fprintf(stderr, "Missing arguments: number=2 precision=10\n");
    } else {
        number = atoi(argv[1]);
        precision = atoi(argv[2]);
    }


    double start = 0;
    double end = number;
    double square = number;
    double error = square * square - number;

    while (error_precision(error) < precision) {
        square = (start + end) / 2;
        error = square * square - number;

        if (error >= 0) {
            end = square;
        } else {
            start = square;
        }

        //printf("%.16f %.16f %e\n", start, end, error);
    }

    printf ("%.20f\n", square);
    return 0;
}
