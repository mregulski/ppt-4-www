#ifndef UTIL
#define UTIL 1
#define DEBUG 1000
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    long swaps;
    long cmps;
} Counter;

Counter *counter()
{
    Counter *c = malloc(sizeof(Counter));
    c->swaps = 0;
    c->cmps = 0;
    return c;
}

typedef struct {
    Counter *count;
    long *array;
} Result;

Result *result()
{
    Result *r = malloc(sizeof(Result));
    r->count = counter();
    r->array = NULL;
    return r;
}

typedef enum {
    Ascending,
    Descending,
    Random
} OrderingE;



void print_result(Result *r, long len, int tabular)
{
    if(tabular)
    {
        printf("%7ld\t%12ld\t%12ld\n",len, r->count->swaps, r->count->cmps);
    }
    else
    {
        printf("size:\t%7ld\tswaps:\t%12ld\tcmps:\t%12ld\n", len, r->count->swaps, r->count->cmps);
    }
}

void print_array(char *str, long *array, long len)
{
    if(str != NULL)
        printf("%s [", str);
    else
        printf("[");
    for(long i = 0; i < len; i++)
    {
        if (i==len-1)
            printf("%ld", array[i]);
        else
            printf("%ld, ", array[i]);
    }
    printf("]\n");
}

void print_key(char *str, long *array, long len, long key_idx)
{
    printf("%s [", str);
    for (long i = 0; i < len; i++)
    {
        if(i == key_idx)
        {
            if (i==len-1)
                printf("*%ld*", array[i]);
            else
                printf("%ld, ", array[i]);
        }
        else
        {
            if (i==len-1)
                printf("%ld", array[i]);
            else
                printf("%ld, ", array[i]);
        }
    }
    printf("]\n");
}

#endif
