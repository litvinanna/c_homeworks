#include <stdio.h>
#include <time.h>
#include "../libs/strings.h"


int main() {

    char alphabet[] = {'a', 't', 'g', 'c'};

    int seqLength = 1000000;
    char seqStr[seqLength + 1];

    for (int i = 0; i < seqLength; ++i) {
        //int num = rand() % 4;
        //char x = alphabet[num];
        //printf("%d   %c %d\n", i, x, num);
        seqStr[i] = alphabet[rand() % 4];
        //str[i] = x;

    }
    seqStr[seqLength] = '\0';
    //printf("seq: %s\n", seqStr);
    BitSeq* seq = createBitSeqFromString(seqStr);

    int position = 1;
    int minPatternLength = 100;
    int maxPatternLength = 100000;


    while (position < seqLength - maxPatternLength) {
        int dummy = 0;
        for (int patternLength = minPatternLength; patternLength < maxPatternLength; patternLength *= 2 ) {
            char patternStr[patternLength + 1];

            strncpy(patternStr, seqStr + position, patternLength);
            patternStr[patternLength] = '\0';

            //printf("%s\n", patternStr);
            BitSeq* pattern = createBitSeqFromString(patternStr);

            clock_t start = clock();
            for (int repeat = 0; repeat < 10; repeat++ ){
                int result = _searchRK(seq, pattern, 0);
                dummy += result;
            }
            clock_t end = clock();

            IntArray sp = prefixes(pattern);
            clock_t start1 = clock();
            for (int repeat = 0; repeat < 10; repeat++ ){
                int result = _searchKMP(seq, pattern, 0, sp);
                dummy += result;
            }
            clock_t end1 = clock();
            deleteArray(sp);



            printf("%8.d\t%8.d\t%.2f\t%.2f\n", position, patternLength, (end - start)/10.0, (end1 - start1)/10.0);


        }
        position *= 2;
    }


    return 0;
}
