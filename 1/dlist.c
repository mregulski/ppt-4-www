#include "list.h"
#include <time.h>

DList *dl_new()
{
    DList *lst = malloc(sizeof(DList));
    lst->first = NULL;
    lst->count = 0;
    return lst;
}

DNode *dnode(list_val_t value)
{
    DNode *n = malloc(sizeof(DNode));
    n->prev = NULL;
    n->next = NULL;
    n->value = value;
    return n;
}

bool dl_isEmpty(DList *list)
{
    return list->first == NULL;
}

bool dl_find(DList *list, list_val_t value)
{
    if(list->first->value== value)  // check first element
        return true;
    DNode *cur = list->first->next; // check the rest
    while(cur != NULL)
    {
        if(cur->value == value)
            return true;
        cur = cur->next;
    }
    return false;

}

void dl_insert(DList *list, int index, list_val_t value)
{
    if(index > list->count)
    {
        fprintf(stderr, "List index out of range.\n");
        exit(EXIT_FAILURE);
    }

    DNode *n = dnode(value);
    if(list->first == NULL)
    {
        n->prev = n;
        n->next = n;
        list->first = n;
        list->count++;
        return;
    }
    if(index == 0)
    {
        n->next = list->first;
        n->prev = list->first->prev;
        list->first->prev->next = n;
        list->first->prev = n;
        list->count++;
        return;
    }
    DNode *cur = list->first;
    for(int i = 1; i < index; i++)
    {
        cur = cur->next;
    }
    n->next = cur->next;
    n->prev = cur;
    cur->next->prev = n;
    cur->next = n;
    list->count++;

}

void dl_print(DList *list)
{
    DNode *cur = list->first;
    if(dl_isEmpty(list)) return;
    do
    {
        printf("%d <- %d -> %d\n", cur->prev->value, cur->value,
                cur->next->value);
        cur = cur->next;
    } while(cur != list->first);
}

void dl_insertStart(DList *list, list_val_t value)
{
    dl_insert(list, 0, value);
}

void dl_insertEnd(DList *list, list_val_t value)
{
    dl_insert(list, list->count, value);
}

void dl_remove(DList *list, int index)
{
    if(index > list->count)
    {
        fprintf(stderr, "list index put of range\n");
        exit(EXIT_FAILURE);
    }

    DNode *cur = list->first;
    for(int i = 0; i < index; i++)
    {
        cur = cur->next;
    }

    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    free(cur);
    list->count--;
}

void dl_free(DList *list)
{
    DNode *cur = list->first;
    while(cur->prev != NULL)
    {
        free(cur->prev);
        cur->prev = NULL;
        cur = cur->next;
    }
    list->count = 0;
    list->first = NULL;
    printf("list cleared\n");
}

list_val_t dl_fetch(DList *list, int index)
{
    if(index > list->count)
    {
        fprintf(stderr, "List index out of range.\n");
        exit(EXIT_FAILURE);
    }
    DNode *cur = list->first;
    if(index > list->count/2)
    {
        for(int i=0; i < list->count-index; i++)
            cur = cur->prev;  
    }
    else
    {
        for(int i=0; i<index; i++)
            cur = cur->next;
    }
    return cur->value;
}

void dl_merge(DList *list1, DList *list2)
{
    DNode *list1f, *list2f, *list1l, *list2l;
    list1f = list1->first;
    list2f = list2->first;
    list1l = list1->first->prev;
    list2l = list2->first->prev;
    list1->first->prev->next = list2f;
    list2->first->prev->next = list1f;
    list2->first->prev = list1l;
    list1->first->prev = list2l;
    list1->count += list2->count;
}
int main()
{/*
    printf("TEST #1\n");
    DList *test = dl_new();
    dl_insertEnd(test, 0);
    dl_insertEnd(test, 1);
    dl_insertEnd(test, 2);
    dl_insertEnd(test, 3);
    dl_insertEnd(test, 4);
    dl_insertEnd(test, 5);
    dl_insertEnd(test, 6);
    dl_insertEnd(test, 7);
    dl_print(test);
    printf("------\n");
    printf("fetch(2): %d\n", dl_fetch(test, 2));
    printf("fetch(5): %d\n", dl_fetch(test, 5));
    printf("fetch(4): %d\n", dl_fetch(test, 4));

    
    printf("--------------------\n");
    printf("TEST #2\n");
    DList *test2 = dl_new();
    dl_insertStart(test2, 0);
    dl_insertStart(test2, 1);
    dl_insertStart(test2, 2);
    dl_insertStart(test2, 3);
    dl_insertStart(test2, 4);
    dl_insertStart(test2, 5);
    dl_insertStart(test2, 6);
    dl_insertStart(test2, 7);
    dl_print(test2);
    printf("------\n");
    dl_merge(test,test2);
    dl_print(test);
    printf("------\n");
    dl_insertStart(test, 8);
    dl_print(test);
    printf("test length: %d\n", test->count);
    printf("fetch(14): %d\n", dl_fetch(test, 14));
    printf("fetch(4): %d\n", dl_fetch(test, 4));
    printf("fetch(8): %d\n", dl_fetch(test, 8));

    printf("--------------------\n"); */
    printf("ACTUAL TEST\n");
    srand(time(0));
    double t_rand = 0;
    double t_245 = 0;
    clock_t start, end;
    int r;
    for(int exCount = 0; exCount < 1000; exCount++)
    {
        DList *list = dl_new();
        for(int i = 0; i < 1000; i++)
        {
            dl_insertEnd(list, rand()%10000);
        }
        start = clock();
        dl_fetch(list, 245);
        end = clock();
        t_245 += (double)(end - start) / CLOCKS_PER_SEC;
        for(int j = 0; j < 100; j++)
        {
            r = rand()%1000;
            start = clock();
            dl_fetch(list, r);
            end = clock();
            t_rand += (double)(end - start) / CLOCKS_PER_SEC;
        }
    }
    printf("[245] avg: %.10f\n", t_245/1000.0);
    printf("[rand] avg: %.10f\n", t_rand/10000.0);
}

