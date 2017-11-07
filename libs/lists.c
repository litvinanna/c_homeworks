#include <stdio.h>

#include "lists.h"
#include "stack.h"


ListItem * createListFromIntArray (IntArray a) {
    ListItem* list = (ListItem *) calloc(1, sizeof(ListItem));
    list->data = a.array[0];
    ListItem* current = list;
    ListItem* next;

    //printf("%d %d \n", list->data, list->next->data);

    for (int i = 1; i < a.length; ++i) {
        next = (ListItem *) calloc(1, sizeof(ListItem));
        next->data = a.array[i];
        current->next = next;
        next->previous = current;
        //printf("%d %d \n", current->data, current->previous->data);
        current = next;
    }

    return list;
}


ListItem* addToList(ListItem * list, int data) {
    ListItem* pointerItem = (ListItem *) calloc(1, sizeof(ListItem));
    pointerItem->data = data;
    pointerItem->next = NULL;

    if (list == NULL) {
        return pointerItem;
    }
    ListItem* current = list;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = pointerItem;
    pointerItem->previous = current;
    return list;
}

ListItem* insertToListByData(ListItem* list, int previousData, int data) {
    ListItem* newItem = (ListItem *) calloc(1, sizeof(ListItem));
    newItem->data = data;
    ListItem* current = list;
    while (current->data != previousData) {
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }

    if (current->next != NULL) {
        current->next->previous = newItem;
    }

    newItem->next = current->next;
    current->next = newItem;
    newItem->previous = current;

    return list;

}


ListItem* insertToListByIndex(ListItem* list, int index, int data) {
    ListItem* newItem = (ListItem *) calloc(1, sizeof(ListItem));
    newItem->data = data;
    ListItem* current = list;
    int currentIndex = 0;

    while (currentIndex != index) {
        if (current->next == NULL) {
            break;
        }
        current = current->next;
        currentIndex += 1;
        //printf("%d %d\n", currentIndex, current->data);
    }

    if (currentIndex < index) {
        current->next = newItem;
        newItem->previous = current;
    } else {
    //printf("out   %d %d\n", currentIndex, current->data);

        if (current->previous != NULL) {
            current->previous->next = newItem;
            newItem->previous = current->previous;
        }
        current->previous = newItem;
        newItem->next = current;

        if (index == 0) {
            list = newItem;
        }
    }
    return list;

}


void printList(ListItem * list) {
    if (list == NULL) {
        printf("list is empty\n");
        return;

    }

    ListItem* current = list;
    printf("[");
    while (current->next != NULL) {
        printf("%d]=>[", current->data);
        current = current->next;
    }
    printf("%d]\n", current->data);
    printf("[");
    while (current->previous != NULL) {
        printf("%d]=>[", current->data);
        current = current->previous;
    }
    printf("%d]\n\n", current->data);
    return;

}

void printListLine(ListItem* list) {
    if (list == NULL) {
        printf("list is empty\n");
        return;

    }
    printf("[");
    while (list->next != NULL) {
        printf("%d, ", list->data);
        list = list->next;
    }
    printf("%d]\n", list->data);
    return;
}


void printListItem(const void* pointer) {
    ListItem * item = (ListItem*) pointer;
    printf("%d ", item->data);
    return;
}



void deleteList(ListItem* list) {
    ListItem * current = list;
    while (current->next != NULL) {
        current = current->next;
        free(current->previous);
        current->previous = NULL;
    }
    free(current);
    current = NULL;

}

// returns NULL if not found!!!!!!!
ListItem* ListSearch(ListItem* list, int data) {
    ListItem* current = list;
    while (current->data != data) {
        if (current->next == NULL) {
            return NULL;
        }
        current = current->next;
    }
    return current;
}


ListItem* ListMerge(ListItem* left, ListItem* right) {
    ListItem* primer = (ListItem *) calloc(1, sizeof(ListItem));
    ListItem* current;
    ListItem* tail;

    primer->data = 0;
    current = primer;

    while (1) {
        if (left->data <= right->data) {
            current->next = left;
            current = left;
            if (left->next == NULL) {
                tail = right;
                break;
            } else {

                left = left->next;
            }
        } else {
            current->next = right;
            current = right;
            if (right->next == NULL) {
                tail = left;
                break;
            } else {
                right = right->next;
            }
        }


    }
    while (1) {
        current->next = tail;
        current = tail;
        if (tail->next == NULL) {
            break;
        } else {
            tail = tail->next;
        }
    }

    ListItem* first = primer->next;
    free(primer);

    return first;
}


ListItem* SorteList(ListItem* list) {
    int i = 0;
    StackVoid* stack = createStackVoid();
    ListItem* current = list;
    //int lastTime = 0;

    while(1) {

        pushStackVoid(stack, current); //push ListItem to stack
        //printListItem(current);
        //printf("\n");

        if (current->next != NULL) {
            current = current->next; //go alond list
        } else {
            break;
        }


        current->previous->next = NULL; //separate current from previous


        if (i%2 == 1) {    //even element in stack is not merged
            int rounds = 0;
            if (i%4 == 1) {  //after each odd element in stack we do merge 1 2 1 3 1 4 1 5 1... times
                rounds = 1;
            } else {
                rounds = i / 4  + 2;
            }
            //printf("merging rounds : %d\n", rounds);
            for (int k = 0; k < rounds; ++k) {
                ListItem* left = (ListItem*) popStackVoid(stack);
                ListItem* right = (ListItem*) popStackVoid(stack);
                ListItem* result = ListMerge(left, right);
                //printf("mergeresult : ");
                //printList(result);
                pushStackVoid(stack, result);
            }
        }
        i += 1;
        //printf("stack:\n");
        //printStackVoid(stack, printListItem);
        //printf("\n\n");
    }



    while(1) {  //final merging of all stack
        ListItem* left = (ListItem*) popStackVoid(stack);
        if (!nonEmptyStackVoid(stack)) {
            list = left; // the end
            break;
        }
        ListItem* right = (ListItem*) popStackVoid(stack);
        ListItem* result = ListMerge(left, right);
        pushStackVoid(stack, result);

    }

    list->previous = NULL; //seperate first element

    current = list;

    while(current->next != NULL) { //re-make all previous element
        current->next->previous = current;
        current = current->next;
    }
    return list;
}



ListItem* reversedList(ListItem* list) {
    if (list->next == NULL) { //if list consists from a single element
        return list;
    }

    ListItem* anchor = list;
    while (anchor->next != NULL) {
        anchor = anchor->next;     // anchor is the last element
    }

    ListItem* current = anchor;
    while(current->previous != NULL) {  //go from anchor to list and reverse "next" pointers using previous
        current->next = current->previous;
        current = current->next;
    }

    current->next = NULL; //make the last element's "next" NULL

    ListItem* prev = anchor; //again start from the last element
    current = anchor->previous;

    anchor->previous = NULL; // make new first element's "previous" NULL

    while (1) {
        current->previous = prev; //fix previous pointers
        prev = prev->next;    //next pointer have already been reversed
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }

    return anchor;
}

ListItem* deleteListItem(ListItem* n) {
    if (n == NULL) {
        return NULL;
    }
    ListItem* list;
    if (n->previous == NULL) {
        if (n->next != NULL) {
            n->next->previous = NULL;
            list = n->next;
        } else {
            list = NULL;
        }
    } else {
        n->previous->next = n->next;
        n->next->previous = n->previous;
        list = n->next;
        while(list->previous != NULL) {
            list = list->previous;
        }
    }
    free(n);
    return list;
}





