#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "strings.h"
#include "lists.h"
#include "arrays.h"

enum {
    a = 0b00,
    t = 0b01,
    g = 0b10,
    c = 0b11
};

int baseToInt(char atgc) {
    if (atgc == 'a') {
        return a;
    } else if (atgc == 't'){
        return t;
    } else if (atgc == 'g') {
        return g;
    } else if (atgc == 'c') {
        return c;
    }
    return a;
}

char intToBase(int n) {
    if (n == a) {
        return 'a';
    } else if (n == t) {
        return 't';
    } else if (n == g) {
        return 'g';
    } else if (n == c) {
        return 'c';
    } else {
        return '-';
    }
}

void appendBitSeq(BitSeq* seq, char letter) { //adds next letter to the BitSeq
    int v = baseToInt(letter) << ((seq->counter % 16) * 2);
    seq->array[seq->counter / 16] |= v;
    seq->counter += 1;
    // printf("%d\n", v);
    return;
}



int getBaseIntFromBitSeq(BitSeq* seq, int pos) { //returns int-letter from position in bitseq
     int n = (seq->array[pos / 16] >> ((pos % 16) * 2)) & 0b11;
     return n;
}

char getFromBitSeq(BitSeq* seq, int pos) { //returns the letter from position in BitSeq
    // int n = ((0x11 << ((pos % 16) * 2)) & seq->array[pos / 16]) >> ((pos % 16) * 2);
    int n = getBaseIntFromBitSeq(seq, pos);
    return intToBase(n);
}

void printBitSeq(BitSeq* seq) {
    for (int i = 0; i < seq->counter; ++i) {
        printf("%c", getFromBitSeq(seq, i));
    }
    printf("\n");
    return;
}



BitSeq* createBitSeqFromString (const char* str) { //creates BitSeq from string
    BitSeq* seq = (BitSeq*) calloc(1, sizeof(BitSeq));
    int seqlen = strlen(str);
    seq->array = (int*) calloc(seqlen / 16 + 1, sizeof(int));
    seq->counter = 0;
    for (int i = 0; i < seqlen; ++i) {
        appendBitSeq(seq, str[i]);
    }
    return seq;
}


int getIntFromBitSeq(BitSeq* seq, int pos) {  //returns 16-bases sequence int
    int positionInSequence = pos / 16;
    int positionInWord = pos % 16;
    // printf("from: %s and: %s\n", int2bin(seq->array[positionInSequence]), int2bin(seq->array[positionInSequence + 1]));
    int first = seq->array[positionInSequence] >> (positionInWord * 2);
    int second = 0;
    if (positionInWord != 0) {
        second = seq->array[positionInSequence + 1] << ((16 - positionInWord) * 2);
        int multMask = ((0b1 << 31) >> (positionInWord * 2 - 1));
        first &= (0xFFFFFFFF ^ multMask);
    }
    // printf("f: %s s: %s\n", int2bin(first), int2bin(second));
    return first | second;
}

BitSeq* getBitSeqFromInt(int n) {
    char str[17] = { '\0' };
    for (int i = 0; i < 16; ++i) {
        char baseStr[2] = { intToBase(n & 0b11), '\0' };
        strcat(str, baseStr);
        n = n >> 2;
    }
    return createBitSeqFromString(str);
}


int maskFromPattern(BitSeq* pattern, int pos) { //return mask for interval in pattern from pos to pos+16
    if ( (pattern->counter - pos) >= 16 ) { //mask includes letters only
        return 0xFFFFFFFF;
    } else {   //mask with zeros for last int in pattern
        int mask = 0;
        for ( int i = 0; i < (pattern->counter - pos); ++i) {
            mask = mask << 2;
            mask = mask | 0b11;
        }
        return mask;
    }

}

char * int2bin(int i)
{
    size_t bits = sizeof(int) * CHAR_BIT;

    char * str = malloc(bits + 1);
    if(!str) return NULL;
    str[bits] = 0;

    // type punning because signed shift is implementation-defined
    unsigned u = *(unsigned *)&i;
    for(; bits--; u >>= 1)
        str[bits] = u & 1 ? '1' : '0';

    return str;
}

int _searchRK (BitSeq* seq, BitSeq* pattern, int searchStartPos) {
    int numberWithTwoLeadingZeros = 0;
    for ( int i = 0; i < 15; ++i) {
        numberWithTwoLeadingZeros = numberWithTwoLeadingZeros << 2;
        numberWithTwoLeadingZeros = numberWithTwoLeadingZeros | 0b11;
    }
    //printf("numberWithTwoLeadingZeros %s\n", int2bin(numberWithTwoLeadingZeros));

    int patternInt = getIntFromBitSeq(pattern, 0);
    int currentInt = getIntFromBitSeq(seq, searchStartPos);
    //printBitSeq(getBitSeqFromInt(currentInt));

    //printBitSeq(getBitSeqFromInt(mask));
    //printf("mask   %s\n", int2bin(mask));
    //printf("patInt %s\n", int2bin(patternInt));
    //printf("curInt %s\n", int2bin(currentInt));
    int mask = maskFromPattern(pattern, 0);

    FIRSTSEARCH:

    while( ((currentInt - patternInt) & mask) !=  0 ) {
        //printf("%d\n", searchStartPos);
        //printf("cur    %s\n", int2bin(currentInt));
        //printBitSeq(getBitSeqFromInt(currentInt));
        //printf("pat %s\n", int2bin(patternInt));
        //printf("mas %s\n", int2bin(mask));
        //printf("res %s\n", int2bin((currentInt - patternInt) & mask));
        if ( (searchStartPos + pattern->counter) > seq->counter) {
            //printf("end reached %d %d\n", searchStartPos, seq->counter);
            return -1;
        }
        currentInt = currentInt >> 2;
        currentInt = currentInt & numberWithTwoLeadingZeros;
        //printf("sd %s\n", int2bin(currentInt));
        currentInt = currentInt | (getBaseIntFromBitSeq(seq, searchStartPos + 16) << 30);
        //printf("nw %s\n", int2bin(getBaseIntFromBitSeq(seq, searchStartPos + 16) << 30));
        //printf("pl %s ", int2bin(currentInt));
        //printBitSeq(getBitSeqFromInt(currentInt));
        //printf("pi %s ", int2bin(patternInt));
        //printBitSeq(pattern);
        searchStartPos += 1;
    } //we've found first part of the pattern

    for (int i = 1; i <= (pattern->counter / 16); ++i) {
        //if ( (searchStartPos + pattern->counter) > seq->counter) {
        //    return -1;
        //}
        //printf("!!!  %d\n", i);
        patternInt = getIntFromBitSeq(pattern, i*16);
        //printBitSeq(getBitSeqFromInt(patternInt));
        currentInt = getIntFromBitSeq(seq, searchStartPos + i*16);
        //printBitSeq(getBitSeqFromInt(currentInt));
        if ( ((currentInt - patternInt) & maskFromPattern(pattern, i*16) ) != 0) {
            goto FIRSTSEARCH;
        }
    }
    return searchStartPos;
}


ListItem* searchRK(BitSeq* seq, BitSeq* pattern) {
    int newPosition = _searchRK(seq, pattern, 0);
    ListItem* result = addToList(NULL, newPosition);
    while (newPosition != -1) {
        newPosition = _searchRK(seq, pattern, newPosition + 1);
        if (newPosition != -1) {
            addToList(result, newPosition);
        }

    }
    return result;
}



IntArray prefixes(BitSeq* seq) {
    int length = seq->counter;
    IntArray prefixes = createIntArray(length);
    prefixes.array[0] = 0;
    for (int i = 1; i < length; ++i) {
        int leaper = i-1;
        int currentLetter = getBaseIntFromBitSeq(seq, i);
        int result = 0;

        while(1) {
            result = prefixes.array[leaper];
            if (currentLetter != getBaseIntFromBitSeq(seq, result)) {
                leaper = result - 1;
                if (leaper < 0) {
                    break;
                }
            } else {
                result += 1;
                break;
            }
        }
        prefixes.array[i] = result;
    }
    return prefixes;
}

 int _searchKMP(BitSeq* seq, BitSeq* pattern, int currentPosInSeq, IntArray sp) {

     if (currentPosInSeq + pattern->counter > seq->counter) {
        return -1;
     }

    //printf("%d \n", currentPosInSeq);
    for (int i = 0; i < pattern->counter; ++i) {  //iteration for pattern
        if (getFromBitSeq(seq, currentPosInSeq + i) == getFromBitSeq(pattern, i)) { //while match
            if (i == pattern->counter - 1) {
                return currentPosInSeq;
            }
            continue;
        } else { // mismatch
            //printf(" mismatch: %d\n", i);

            int shift = sp.array[i];
            currentPosInSeq  += i - shift + 1;
            return _searchKMP(seq, pattern, currentPosInSeq, sp);
        }
    }
    return -2;

}
ListItem* searchKMP (BitSeq* seq, BitSeq* pattern) {
    IntArray sp = prefixes(pattern);
    int newPosition = _searchKMP(seq, pattern, 0, sp);
    ListItem* result = addToList(NULL, newPosition);
    while (newPosition > -1) {
        newPosition = _searchKMP(seq, pattern, newPosition + 1, sp);
        if (newPosition > -1) {
            addToList(result, newPosition);
        }

    }
    return result;

}


