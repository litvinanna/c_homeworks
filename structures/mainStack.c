#include "stacketal.h"
#include "structures.h"
#include "../arrays/array.h"


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

/*    Stack* stack = createStack();
    printStack(stack);
    pushStack(stack, 55);
    pushStack(stack, 1);
    printStack(stack); */



/*    Queue* queue = createQueue();
    pushQueue(queue, 1);
    pushQueue(queue, 4);
    printQueue(queue);

    printf("%d\n", popQueue(queue));
    printf("%d\n", popQueue(queue));
    printQueue(queue);

    StackLong *s = createStackLong();

    int *a = (int *) calloc(1, sizeof(int));
    *a = 10;

    pushStackLong(s, (long long) a);

    int *pointer = (int *) popStackLong(s);
    printf("%d\n", *pointer);
*/
    IntArray a = createRandomIntArray(8);
    //a.array[0] = 1;
    //a.array[1] = 1;
    ListItem* list1 = createListFromIntArray(a);
    deleteArray(a);
    printList(list1);

    // IntArray b = createNaturalIntArray(1);
    //b.array[0] = 2;
    //b.array[1] = 3;
    // ListItem* list2 = createListFromIntArray(b);
    // deleteArray(b);
    // printList(list2);

    // ListItem *merged = ListMerge(list1, list2);
    // printList(merged);

    //IntArray b = createNaturalIntArray(1);
    //ListItem* list1 = createListFromIntArray(b);
    //deleteArray(b);

    //printList(ListMerge(list, list1));


    ListItem* list = SortedList(list1);

    printList(list);

    return 0;
}
