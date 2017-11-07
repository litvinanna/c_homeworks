/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rule.h
 * Author: pochtalionizm
 *
 * Created on 29 сентября 2017 г., 0:45
 */

#ifndef RULE_H
#define RULE_H

typedef enum {
    STAY = 0,
    LEFT = 1,
    RIGHT = 2
} Move;

typedef struct {
    const char *state;
    char symbol;
    char newSymbol;
    const char *nextState;
    Move move;
} Rule;

#endif /* RULE_H */
