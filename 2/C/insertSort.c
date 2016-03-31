#ifndef INSERT
#define INSERT 1
#include "util.h"
#include <string.h>

Result *insert_sort(long *array, long len, int logging)
{
    Result *r = result();
    // work on a copy, to allow reuse of array in multiple tests
    long *sorted = malloc(sizeof(long)*len);
    sorted = memcpy(sorted, array, sizeof(long)*len);

    long key, j;
    for(long i=1; i < len; i++)
    {
        key = sorted[i];
        if(logging > 3)
        {
            printf("key: %ld\n", key);
            print_array("before:", sorted, len);
        }
        j = i - 1;
        // must use pre-incrementation because cmps start at 0
        if(logging > 2)
        {
            printf("compare: %ld@[%ld], %ld\n", sorted[j], j, key);
        }
        while (++r->count->cmps && j >= 0 && sorted[j] > key)
        {
            if(logging > 2)
            {
                printf("compare: %ld@[%ld], %ld\n", sorted[j], j, key);
                printf("pushing %ld@[%ld] to [%ld]\n", sorted[j], j, j+1);
            }
            sorted[j+1] = sorted[j];
            r->count->swaps++;
            j--;
        }
        sorted[j+1] = key;
        r->count->swaps++;
        if(logging > 3)
        {
            print_array("after:", sorted, len);
        }
    }
    r->array = sorted;
    return r;
}

Result *insert_sort_nocopy(long *array, long len, int logging, Result *r)
{
    long key, j;
    for(long i=0; i < len; i++)
    {
        key = array[i];
        if(logging > 3)
        {
            printf("key: %ld\n", key);
            print_array("before:", array, len);
        }
        j = i - 1;
        // must use pre-incrementation, othrewise condition is wrong at first pass
        while (++r->count->cmps && j >= 0 && array[j] > key)
        {
            if(logging > 2)
            {
                printf("compare: %ld@[%ld], %ld\n", array[j], j, key);
            }
            array[j+1] = array[j];
            r->count->swaps++;
            j--;
        }
        array[j+1] = key;
        r->count->swaps++;
        if(logging > 3)
        {
            print_array("after:", array, len);
        }
    }

    return r;
}
#endif
