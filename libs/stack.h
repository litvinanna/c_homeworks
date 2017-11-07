#ifndef STACK_GUARD_H
#define STACK_GUARD_H

typedef struct StackStruct {
    int* pit;
    int depth;
    int head;
} Stack;


Stack* createStack();
void pushStack(Stack* stackP, int n);
int popStack(Stack* stackP);
void removeStack(Stack* stackP);
int peekStack(Stack* stackP);
int nonEmptyStack (Stack* stackP);
void printStack(Stack* stackP);

typedef struct QueueItemStruct{
    int data;
    struct QueueItemStruct* next;
} QueueItem;


typedef struct {
    QueueItem* head;
    QueueItem* tail;
} Queue;

Queue* createQueue();
void pushQueue(Queue* queueP, int n);
int popQueue(Queue* queueP);
int peekQueue(Queue* queueP);
int nonEmptyQueue(Queue* queueP);
void printQueue(Queue* queueP);




/*---------------Stack of Pointers--------------------------------*/



typedef void (* PrintFunction)(const void *pointer);

typedef struct StackVoidStruct {
    void* * pit;
    int depth;
    int head;
} StackVoid;

StackVoid* createStackVoid();
void pushStackVoid(StackVoid* stackP, void * n);
void* popStackVoid(StackVoid* stackP);
void* peekStackVoid(StackVoid* stackP);
int nonEmptyStackVoid(StackVoid* stackP);
void printStackVoid(StackVoid* stackP, PrintFunction f);




/*-----------------Stack of doubles --------------------------------------------------------*/



typedef struct StackDoubleStruct {
    double* pit;
    int depth;
    int head;
} StackDouble;


StackDouble* createStackDouble();
void pushStackDouble(StackDouble* stackP, double n);
double popStackDouble(StackDouble* stackP);
double peekStackDouble(StackDouble* stackP);
int nonEmptyStackDouble(StackDouble* stackP);
void printStackDouble(StackDouble* stackP);

#endif // STACK_GURAD_H

