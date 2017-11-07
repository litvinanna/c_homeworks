/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: pochtalionizm
 *
 * Created on 29 сентября 2017 г., 0:43
 */

#include <stdio.h>
#include <stdlib.h>

#include "turing.h"

/*
 * 
 */
int main(int argc, char** argv) {

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
    
    char *initialState = (char *) calloc(256, sizeof(char));
    char *initialWord = (char *) calloc(256, sizeof(char));
    int initialPosition;
    char defaultSymbol;
    fscanf(file, "%s %s %d %c\n", initialState, initialWord, &initialPosition, &defaultSymbol);
    
    
    
    TuringMachine *machine = create(initialState, initialWord, initialPosition, defaultSymbol);
    
    //%s - string until space
    //%c - single char
    //%d - integer until space or not a number (e.g 123abc will be readed as 123)
    

    
    
    while (!feof(file)) {
        char *state = (char *) calloc(256, sizeof(char));
        char *nextState = (char *) calloc(256, sizeof(char));
        char symbol;
        char newSymbol;
        Move mode;
        
        fscanf(file, "%s %c %c %s %u\n", state, &symbol, &newSymbol, nextState, &mode);
        addRule (machine, state, symbol, newSymbol, nextState, mode);
    }
    
    //mode - STAY = 0, LEFT = 1, RIGHT = 2

    
    while (machine->terminated == 0) {
        print(machine);
        step(machine);
    }
    print(machine);
    return (EXIT_SUCCESS);
}

