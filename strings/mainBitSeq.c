
#include <stdio.h>
#include "../libs/strings.h"
#include "../libs/lists.h"

int main() {
    const char *str = "tattaatttatattatatat";
    BitSeq* seq = createBitSeqFromString(str);
    printBitSeq(seq);

    const char* p = "tatat";
    BitSeq* pattern = createBitSeqFromString(p);
    printBitSeq(pattern);


    IntArray sp = prefixes(pattern);
    printArray(sp);

    ListItem* result = searchKMP(seq, pattern);
    printListLine(result);

    return 0;
}
