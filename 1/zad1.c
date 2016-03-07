#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int value;
    Node *next;
} Node;

typedef struct {
    Node *top;
    Node *end;
} Queue;

Queue *queue_new()
{
    Queue * q = malloc(sizeof(Queue));
    q->top = NULL;
    q->end = NULL;
    return q;
}

bool queue_isEmpty(Queue *q)
{
    return q->top == q->end;
}
