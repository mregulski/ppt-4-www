#include "list.h"
#include <time.h>
List *l_new()
{
    List *lst = malloc(sizeof(List));
    lst->first = NULL;
    lst->count = 0;
    return lst;
}

SNode *snode(int value)
{
    SNode *n = malloc(sizeof(SNode));
    n->value = value;
    return n;
}

bool l_isEmpty(List *list)
{
    return list->first == NULL;
}

bool l_find(List *list, int value)
{
    SNode *cur = list->first;
    while(cur != NULL)
    {
        if(cur->value == value)
            return true;
        cur = cur->next;
    }
    return false;
}
void l_insertStart(List *list, list_val_t value)
{
    l_insert(list, 0, value);
}

void l_insertEnd(List *list, list_val_t value)
{
    l_insert(list, list->count, value);
}

void l_insert(List *list, int index, list_val_t value)
{
    if(index > list->count)
    {
        fprintf(stderr, "List index out of range.\n");
        exit(EXIT_FAILURE);
    }
    SNode *n = snode(value);
    SNode *tmp;
    if(list->first == NULL)
    {
        list->first = n;
        list->count++;
        return;
    }
    if(index == 0)
    {
        n->next = list->first;
        list->first = n;
        list->count++;
        return;
    }

    SNode *cur = list->first;
    for(int i = 1; i < index; i++)
    {
        cur = cur->next;
    }
    tmp = cur->next;
    cur->next = n;
    n->next = tmp;
    list->count++;
}

void l_print(List *list)
{
    SNode *cur = list->first;
    printf("list size: %d.\n", list->count);
    while(cur != NULL)
    {
        printf("%d\n", cur->value);
        cur = cur->next;
    }
    printf("----------------\n");

}

list_val_t l_fetch(List *list, int index)
{
    if(index > list->count)
    {
        fprintf(stderr, "List index out of range.\n");
        exit(EXIT_FAILURE);
    }
    SNode *cur = list->first;
    for(int i = 0; i<index; i++)
    {
        cur = cur->next;
    }
    return cur->value;
}

void l_free(List *list)
{
    SNode *cur = list->first;
    while(cur != NULL)
    {
        list->first = list->first->next;
        free(cur);
        cur = list->first;
    }
    list->first = NULL;
    list->count = 0;
}

void l_remove(List *list, int index)
{
    if(index > list->count)
    {
        fprintf(stderr, "list index out of range\n");
        exit(EXIT_FAILURE);
    }

    SNode *cur = list->first;
    SNode *tmp;
    for(int i = 0; i < index-1; i++)
    {
        cur = cur->next;
    }
    tmp = cur->next;
    cur->next = cur->next->next;
    free(tmp);
    list->count--;
}

// make list1 equal to list1+list2
// list1 cant be null
void l_merge(List *list1, List *list2)
{
    if(list1 == NULL)
    {
        fprintf(stderr, "List1 is null. merge will have no effect.\n");
        return;
    }
    if(list2 == NULL)
        return;

    SNode *last = list1->first;
    while(last->next != NULL)
    {
        last = last->next;
    }
    last->next = list2->first;
    list1->count += list2->count;

}

int main()
{/*
    printf("TEST #1 - basics\n");
    List *test = l_new();
    l_insertEnd(test, 0);
    l_insertEnd(test, 1);
    l_insertEnd(test, 2);
    l_insertEnd(test, 3);
    l_remove(test, 2);
    l_print(test);
    printf("test[2] = %d\n", l_fetch(test,2));
    
    printf("\nTEST #2 - merge\n");
    List *test2 = l_new();
    l_insertEnd(test2, 4);
    l_insertEnd(test2, 5);
    l_merge(test, NULL);
    l_print(test);
    printf("merge(test, NULL) success\n");
    List *test3 = NULL;
    printf("merge(NULL,test) success\n");

    printf("\nTEST #3 - access time\n");
    */
    srand(time(0));
    double t_rand = 0;
    double t_245 = 0;
    clock_t start, end;
    for(int e = 0; e < 1000; e++)
    {
        List *list = l_new();
        for(int i = 0; i < 1000; i++)
        {
            l_insertEnd(list, rand()%10000);
        }
         

        start = clock();
        l_fetch(list, 245);
        end = clock();
        t_245 += (double)(end-start) / CLOCKS_PER_SEC;
        for(int j = 0; j< 100; j++)
        {
            int r = rand()%1000;
            start = clock();
            l_fetch(list, r);
            end = clock();
            t_rand += (double)(end-start) / CLOCKS_PER_SEC;
        }

        l_free(list);
        free(list);
    } 
    printf("[245] avg: %.10f\n", t_245/1000.0);
    printf("[rand()] avg: %.10f\n", t_rand/10000.0);

}
