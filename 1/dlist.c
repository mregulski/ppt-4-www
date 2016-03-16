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

int main()
{
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
}

