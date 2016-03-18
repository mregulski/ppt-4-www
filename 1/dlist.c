#include "list.h"
#include <sys/time.h>
#include <time.h>

DList *dl_new()
{
    DList *lst = (DList*) malloc(sizeof(DList));
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
    if(index >= list->count)
    {
        fprintf(stderr, "[fetch] List index (%d) out of range (0..%d).\n",
        index, list->count-1);
        //exit(EXIT_FAILURE);
    }
    DNode *cur = list->first;
    if(index == 0)
    {
    //    printf("feetching 0\n");
        return list->first->value;
    }
    if(index == list->count-1)
    {
    //    printf("fetching last (%d)\n", index);
        return list->first->prev->value;
    }
    if(index > list->count/2)
    {
    //    printf("fetching half(%d)\n", list->count/2);
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

long measure_time(DList *list, int index, int verbose);
void dl_merge(DList *list1, DList *list2)
 {
    DNode *list1f, *list2f, *list1l, *list2l;
    /* keep 'terminal' nodes on both lists */
    list1f = list1->first;
    list2f = list2->first;
    list1l = list1->first->prev;
    list2l = list2->first->prev;

    /* stitch the ends together */
    list1->first->prev->next = list2f;
    list2->first->prev->next = list1f;
    list2->first->prev = list1l;
    list1->first->prev = list2l;
    /* update count */
    list1->count += list2->count;
}
#define TESTS 1000
#define R_TESTS 100
#define LIST_SIZE 1000
int main(int argc, char**argv)
{
    int tests = TESTS;
    int r_tests = R_TESTS;
    int verbose = 0;
    int list_size = LIST_SIZE;
    if(argc == 2)
    {
        verbose = atoi(argv[1]);
    }
    if(argc == 5)
    {
        tests = atoi(argv[1]);
        r_tests = atoi(argv[2]);
        list_size = atoi(argv[3]);
        verbose = atoi(argv[4]);
    }

    //printf("TEST #1\n");
    if(verbose)
    {
        DList *test = dl_new();
        for(int i = 0; i < 8; i++)
            dl_insertEnd(test, i);

        dl_insert(test, 4, 4444);
        DList *test2 = dl_new();
        for(int i = 0; i < 8; i++)
            dl_insertStart(test2, i);

        dl_merge(test,test2);

        dl_print(test);
        printf("test->length = %d\n", test->count);
        printf("dl_fetch(test, 0) = %d\n", dl_fetch(test, 0));
        printf("dl_fetch(test, 4) = %d\n", dl_fetch(test, 4));
        printf("dl_fetch(test, test->count) = %d\n", dl_fetch(test, test->count));
        printf("dl_fetch(test, test->count-1) = %d\n", dl_fetch(test, test->count-1));
    }
    //getchar();
    printf("ACCESS TIME TEST\n");
    srand(time(0));
    long t_rand = 0;
    long t_half = 0;
    long t_first = 0;
    long t_last = 0;
    int r;
    long r_sum = 0;

    DList **lists = malloc(sizeof(DList*) * tests);

    /* create a list for each test */
    for(int exCount = 0; exCount < tests; exCount++)
    {
      lists[exCount] = dl_new();
      for(int i = 0; i < list_size; i++)
      {
          dl_insertStart(lists[exCount], rand()%10000);
      }
    }

    /*********************
        access time tests
     *********************/
    for(int e = 0; e < tests; e++)
    {
    // first element
    if(verbose)
    {
        printf("Test #%d\n", e);
        printf("\t%-8s ", "[FIRST]");
    }
    t_first += measure_time(lists[e], 1, verbose);

    // last element
    if(verbose)
        printf("\t%-8s ", "[LAST]");
    t_last  += measure_time(lists[e], lists[e]->count-1, verbose);

    // middle element
    if(verbose)
        printf("\t%-8s ", "[HALF]");
    t_half  += measure_time(lists[e], lists[e]->count/2, verbose);

    // random element
    r = rand()%list_size;
    r_sum += r;
    if(verbose)
        printf("\t%-8s ", "[RAND]");
    t_rand  += measure_time(lists[e], r, verbose);
    }
    // print results
    printf("%-8s avg: %f, total: %ld\n", "[FIRST]",
        (double)t_first/(double)(tests), t_first);
    printf("%-8s avg: %f, total: %ld\n", "[LAST]",
        (double)t_last/(double)(tests), t_last);
    printf("%-8s avg: %f\n", "[HALF]", (double)t_half/(double)(tests));
    printf("%-8s avg: %f | avg rand(): %ld\n", "[RAND]",
        (double)t_rand/(double)tests, r_sum/tests);
}

long measure_time(DList *list, int index, int verbose)
{
    struct timeval start, end;

    gettimeofday(&start, NULL);
    dl_fetch(list, index);
    gettimeofday(&end, NULL);
    if(verbose)
        printf("fetch %4d, start: %8ld, end: %8ld, time: %2ld\n",
            index, start.tv_usec, end.tv_usec, end.tv_usec - start.tv_usec);
    return end.tv_usec - start.tv_usec;
}
