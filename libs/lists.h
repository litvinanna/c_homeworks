#ifndef LIST_GUARD_H
#define LIST_GUARD_H

#include "lists.h"
#include "arrays.h"

typedef struct ListItemStruct {
    struct ListItemStruct * previous;
    struct ListItemStruct * next;
    int data;
} ListItem;

ListItem * createListFromIntArray (IntArray a);
ListItem* addToList(ListItem* list, int data);
void printList(ListItem * list);
void printListLine(ListItem* list);
void printListItem (const void * list);
void deleteList(ListItem* list);

ListItem* ListSearch(ListItem* list, int data);
ListItem* insertToListByData(ListItem* list, int previousData, int data);
ListItem* insertToListByIndex(ListItem* list, int index, int data);
ListItem* ListMerge(ListItem* left, ListItem* right);
ListItem* SorteList(ListItem* list);
ListItem* reversedList(ListItem* list);

ListItem* deleteListItem(ListItem* n);

#endif // LIST_GURAD_H
