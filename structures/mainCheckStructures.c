#include "structures.h"
//#include"../arrays/array.h"
//#include "stacketal.c"

int main(int argc, char **argv) {
    IntArray a = createNaturalIntArray(8);
    ListItem* list = createListFromIntArray(a);
    printf("create list\n");
    printList(list);

    list = insertToListByIndex(list, 1, 111);
    printList(list);

    list = insertToListByData(list, 4, 444);
    printList(list);

    addToList(list, 999);
    printf("add to list\n");
    printList(list);

    ListItem* b = ListSearch(list, 3);
    if (b != NULL) {
        printListItem(b);
        printf("\n");
    } else printf(":(\n");

    list = reversedList(list);
    printf("reversed list\n");
    printList(list);

    list = SortedList(list);
    printf("sorted list\n");
    printList(list);

    ListItem* new1 = addToList(NULL, 3);
    printList(new1);

    new1 = reversedList(new1);
    printList(new1);

    return 0;
}
