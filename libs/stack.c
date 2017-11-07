#include <stdlib.h>
#include <stdio.h>

#include "arrays.h"
#include "stack.h"


Stack* createStack(){
    Stack* stack = (Stack*) calloc(1, sizeof(Stack));
    stack->depth = 16;
    stack->head = -1;
    stack->pit = (int*) calloc(16, sizeof(int));
    return stack;
}

void pushStack(Stack* stackP, int n) {
    if (stackP->depth < stackP->head + 2) {
        stackP->pit = (int *) realloc(stackP->pit, stackP->depth * 2 * sizeof(int));
        stackP->depth *= 2;
    }
    stackP->head += 1;
    stackP->pit[stackP->head] = n;
    return;
}

int popStack(Stack* stackP) {
    int last = stackP->pit[stackP->head];
    stackP->head -= 1;
    return last;
}

void removeStack(Stack* stackP) {
    stackP->head -= 1;
    return;
}

int peekStack(Stack* stackP) {
    int last = stackP->pit[stackP->head];
    return last;
}
int nonEmptyStack (Stack* stackP) {
    if (stackP->head < 0) {
        return 0;
    } else {
        return 1;
    }
}

void printStack(Stack* stackP) {
    for (int i = 0; i <= stackP->head; ++i) {
        printf("%d ", stackP->pit[i]);
    }
    printf("\n");
    return;
}


Queue* createQueue () {
    Queue* queue = (Queue*) calloc(1, sizeof(Queue));
    return queue;
}

void pushQueue(Queue* queueP, int n) {
    QueueItem* item = (QueueItem*) calloc(1, sizeof(QueueItem));
    item->data = n;
     if (queueP->head == NULL) {
            queueP->head = item;
    } else  {
        queueP->tail->next = item;
    }
    queueP->tail = item;
    return;
}

int popQueue(Queue* queueP) {
    int first = queueP->head->data;
    QueueItem* newhead = queueP->head->next;
    queueP->head = newhead;
    return first;
}

int peekQueue(Queue* queueP){
    int first = queueP->head->data;
    return first;
}

int nonEmptyQueue(Queue* queueP) {
    if (queueP->head != NULL) {
        return 1;
    } else {
        return 0;
    }
}


void printQueue(Queue* queueP) {
    if (queueP->head == NULL) {
        printf("\n");
        return;
    }
    QueueItem* current = queueP->head;
    while (current->next != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("%d\n", current->data);
    return;
}



/*---------------Stack of Pointers--------------------------------*/




StackVoid* createStackVoid(){
    StackVoid* stack = (StackVoid*) calloc(1, sizeof(StackVoid));
    stack->depth = 16;
    stack->head = -1;
    stack->pit = (void**) calloc(16, sizeof(void*));
    return stack;
}

void pushStackVoid(StackVoid* stackP, void * n) {
    if (stackP->depth <= stackP->head + 2) {
        stackP->pit = (void**) realloc(stackP->pit, stackP->depth * 2 * sizeof(void *));
        stackP->depth *= 2;
    }
    stackP->head += 1;
    stackP->pit[stackP->head] = n;
    // printf("push\n");
    return;
}

void* popStackVoid(StackVoid* stackP) {
    void * last = stackP->pit[stackP->head];
    stackP->head -= 1;
    return last;
}

void* peekStackVoid(StackVoid* stackP) {
    void* last = stackP->pit[stackP->head];
    return last;
}

int nonEmptyStackVoid (StackVoid* stackP) {
    if (stackP->head < 0) {
        return 0;  //false
    } else {
        return 1; //true
    }
}


void printStackVoid(StackVoid* stackP, PrintFunction f) {
    for (int i = 0; i <= stackP->head; ++i) {
        f(stackP->pit[i]);
    }
    printf("\n");
    return;
}

/*-----------------Stack of doubles --------------------------------------------------------*/




StackDouble* createStackDouble(){
    StackDouble* stack = (StackDouble*) calloc(1, sizeof(StackDouble));
    stack->depth = 16;
    stack->head = -1;
    stack->pit = (double *) calloc(16, sizeof(double));
    return stack;
}

void pushStackDouble(StackDouble* stackP, double n) {
    if (stackP->depth < stackP->head + 2) {
        stackP->pit = (double *) realloc(stackP->pit, stackP->depth * 2 * sizeof(double));
        stackP->depth *= 2;
    }
    stackP->head += 1;
    stackP->pit[stackP->head] = n;
    return;
}

double popStackDouble(StackDouble* stackP) {
    double last = stackP->pit[stackP->head];
    stackP->head -= 1;
    return last;
}

double peekStackDouble(StackDouble* stackP) {
    double last = stackP->pit[stackP->head];
    return last;
}
int nonEmptyStackDouble (StackDouble* stackP) {
    if (stackP->head < 0) {
        return 0; //false
    } else {
        return 1; //true
    }
}

void printStackDouble(StackDouble* stackP) {
    for (int i = 0; i <= stackP->head; ++i) {
        printf("%.f ", stackP->pit[i]);
    }
    printf("\n");
    return;
}

