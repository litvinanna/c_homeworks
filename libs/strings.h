#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

#include "lists.h"

typedef struct bitSeqStruct{
    int* array;
    int counter;
} BitSeq;

BitSeq* createBitSeqFromString (const char* str);
void printBitSeq(BitSeq* seq);
int getIntFromBitSeq(BitSeq* seq, int pos);
BitSeq* getBitSeqFromInt(int n);

int _searchRK(BitSeq* seq, BitSeq* pattern, int searchStartPos);
ListItem* searchRK (BitSeq* seq, BitSeq* pattern);


int maskFromPattern(BitSeq* pattern, int pos);
char * int2bin(int i);

IntArray prefixes(BitSeq* seq);
int _searchKMP(BitSeq* seq, BitSeq* pattern, int pos, IntArray prefixes);
ListItem* searchKMP (BitSeq* seq, BitSeq* pattern);
#endif // STRINGS_H_INCLUDED
