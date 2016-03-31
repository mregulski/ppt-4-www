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

void print_result(Result *r, long len, long time, int tabular)
{
    if(tabular)
    {
        printf("\t%7ld\t%12ld\t%12ld\t%6ld\n",len, r->count->swaps, r->count->cmps, time);
    }
    else
    {
        printf("size:\t%7ld\tswaps:\t%12ld\tcmps:\t%12ld\n", len, r->count->swaps, r->count->cmps);
    }
}


#define NO_SPECIAL -1
void print_array(char *str, long *array, long len, long special_idx)
{
    if(str != NULL)
        printf("%s [", str);
    else
        printf("[");
    for(long i = 0; i < len; i++)
    {
        if (i==len-1)
        {
            if(i==special_idx)
                printf("*%ld*", array[i]);
            else
                printf("%ld", array[i]);
        }
        else
        {
            if(i==special_idx)
                printf("*%ld*,", array[i]);
            else
                printf("%ld,", array[i]);
        }
    }
    printf("]\n");
}


void print_array_range(char *str, long *array, long start, long stop, long special_idx)
{
    if(str != NULL)
        printf("%s [", str);
    else
        printf("[");
    for(long i = start; i <= stop; i++)
    {
        if (i==stop)
        {
            if(i==special_idx)
                printf("*%ld*", array[i]);
            else
                printf("%ld", array[i]);
        }
        else
        {
            if(i==special_idx)
                printf("*%ld*,", array[i]);
            else
                printf("%ld,", array[i]);
        }
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

// fancy printer
void indent(int level)
{
    for(int i = 0; i < level; i++)
    {
        printf("--- ");
    }
}

#endif
