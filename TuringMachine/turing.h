/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   turing.h
 * Author: pochtalionizm
 *
 * Created on 29 сентября 2017 г., 0:44
 */

#ifndef TURING_H
#define TURING_H

#include "rule.h"

typedef struct {
    char defaultSymbol;
    
    int ruleCount;
    Rule *rules;
    
    int position;
    char *stream;
    
    int printStart;
    int printEnd;

    const char *currentState;
    
    int terminated;
} TuringMachine;

TuringMachine* create(const char *initialState, const char *initialWord, int initialPosition, char defaultChar);
void addRule(TuringMachine *machine, const char *state, char symbol, char newSymbol, const char *nextState, Move move);
void print(TuringMachine *machine);
void step(TuringMachine *machine);
void destroy(TuringMachine *machine);

#endif /* TURING_H */
