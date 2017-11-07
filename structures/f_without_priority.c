#include <stdio.h>
#include <stdlib.h>
#include "stacketal.h"


/*
(   0
+   1
-   2
*   3
/   4
)   5


*/


int charIsOperation (char s) {
    if (s == '(') {
        return 0;
    }
    if (s ==  '+') {
        return 1;
    }
    if (s == '-') {
        return 2;
    }
    if (s ==  '*') {
        return 3;
    }
    if (s ==  '/') {
        return 4;
    }
    if (s ==  ')') {
        return 5;
    }
    return -1;
}

int levelOfOperation (int operation) {
    if (operation == 1 || operation == 2) { // + -
        return 2;
    }
    if (operation == 3 || operation == 4) { // * /
        return 2;
    }
    if (operation == 0) {
        return 0;
    }
    if (operation == 5) {
        return 3;
    }
    return -1;
}


void makeLastOperation(StackDouble* numbers, Stack* operations) {
    double y = popStackDouble(numbers);
    double x = popStackDouble(numbers);
    int operation = popStack(operations);
    double result = 0.0;

    if (operation == 1) {
        result = x + y;
    }
    if (operation == 2) {
        result = x - y;
    }
    if (operation == 3) {
        result = x * y;
    }
    if (operation == 4) {
        result = x / y;
        // printf("%f fff\n", result);
    }

    pushStackDouble(numbers, result);
    return;

}

int intFromChar(char c) {
    char str[2];
    str[0] = c;
    str[1] = '\0';
    return atoi(str);
}

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


    StackDouble* numbers = createStackDouble();
    Stack* operations = createStack();
    //pushStack(operations, 0);


    while (!feof(file)) {

        char first;
        int scanResult = fscanf(file, "%c", &first);

        if (first == ' ' || feof(file) || first == '\n' || first == '\0' || scanResult == 0) continue;

        int integer;
        double doublenumber;

        integer = charIsOperation(first);
        if (integer == -1) { // it is a number
            doublenumber = (double) intFromChar(first);
            while (1) {
                int result = fscanf(file, "%c", &first);
                if (first == ' ' || feof(file) || first == '\n' ||first == '\0' || result == 0) {
                    break;
                }
                //printf("%c\n", first);
                doublenumber = doublenumber * 10 + (double) intFromChar(first);
            }
            pushStackDouble(numbers, doublenumber);

        } else  {    // it is an operation
            if (integer == 5) { //current operation is )
                while (peekStack(operations) != 0) {
                    makeLastOperation(numbers, operations);
                }
                popStack(operations);

            } else if (nonEmptyStack(operations)) { // stack is not empty
                int previous = peekStack(operations); //

                if (previous == 0){ //previous is (
                    pushStack(operations, integer);

                } else { //previous is + - * -
                    if (levelOfOperation(previous) <= levelOfOperation(integer) ) {
                        makeLastOperation(numbers, operations);
                    }
                    pushStack(operations, integer);
                }

            } else { // stack is empty
                pushStack(operations, integer);
            }

        }


        printf("numbers stack: ");
        printStackDouble(numbers);
        printf("operations stack: ");
        printStack(operations);
        printf("\n");
    }

    while(nonEmptyStack(operations)) {
        makeLastOperation(numbers, operations);
        // printf("!");
    }

    double result = popStackDouble(numbers);
    printf("%f\n", result);
    return 0;
}
