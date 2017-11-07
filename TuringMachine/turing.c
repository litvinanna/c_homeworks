/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   turing.c
 * Author: pochtalionizm
 * 
 * Created on 29 сентября 2017 г., 0:44
 */

#include "turing.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

TuringMachine* create(const char *initialState, const char *initialWord, int initialPosition, char defaultChar) {
    TuringMachine *machine = (TuringMachine *) calloc(1, sizeof(TuringMachine));
    
    machine->currentState = initialState;
    machine->ruleCount = 0;
    machine->rules = (Rule *) calloc(100, sizeof(Rule));
    machine->stream = (char *) calloc(100000, sizeof(char));
    memset(machine->stream, defaultChar, 100000 * sizeof(char));
    machine->defaultSymbol = defaultChar;
    machine->position = 50000;
    machine->printStart = machine->position;
    
    int wordLength = strlen(initialWord);
    int k = 0;
    for (int i = machine->position; i < machine->position + wordLength; ++i) {
        machine->stream[i] = initialWord[k];
        k += 1;
    }
    machine->position += initialPosition;
    machine->printEnd = machine->position + wordLength;
    machine->terminated = 0;
    
    return machine;
}

void print(TuringMachine *machine) {
    for (int i = machine->printStart - 0; i < machine->printEnd + 0; ++i) {
        printf("%c", machine->stream[i]);
    }
    //printf("\n");
    printf("\t%d\n", machine->position - machine->printStart);
}

void addRule(TuringMachine *machine, const char *state, char symbol, char newSymbol, const char *nextState, Move move) {
    machine->rules[machine->ruleCount].state = state;
    machine->rules[machine->ruleCount].symbol = symbol;
    machine->rules[machine->ruleCount].newSymbol = newSymbol;
    machine->rules[machine->ruleCount].nextState = nextState;
    machine->rules[machine->ruleCount].move = move;
    machine->ruleCount += 1;
}

void destroy(TuringMachine *machine) {
    free(machine->stream);
    free(machine->rules);
    free(machine);
}

void step(TuringMachine *machine) {
    const char currentSymbol = machine->stream[machine->position];
    const char *currentState = machine->currentState;
    for (int i = 0; i < machine->ruleCount; ++i) {
        const Rule rule = machine->rules[i];
        if (strcmp(rule.state, currentState) == 0 && rule.symbol == currentSymbol) {
            machine->stream[machine->position] = rule.newSymbol;
            machine->currentState = rule.nextState;
            switch (rule.move) {
                case STAY:
                    break;
                case LEFT:
                    machine->position -= 1;
                    break;
                case RIGHT:
                    machine->position += 1;
                    break;
            }
        } 
    }
    if (strcmp(machine->currentState, "qt") == 0) machine->terminated = 1;
    if (machine->position > machine->printEnd) machine->printEnd = machine->position;
    if (machine->position < machine->printStart) machine->printStart = machine->position;
}
