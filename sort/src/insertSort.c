#include "util.h"
#include "sort.h"
#include <string.h>

Result *insert_sort(long *array, long len, int logging)
{
    Result *r = result();
    // work on a copy, to allow reuse of array in multiple tests
    long *sorted = malloc(sizeof(long)*len);
    sorted = memcpy(sorted, array, sizeof(long)*len);
    if(logging > 1)
    {
        print_array("array:", array, len, NO_SPECIAL);
        print_array(" copy:", sorted, len, NO_SPECIAL);
        printf("start\n\n");
    }
    long key, j;
    for(long i=1; i < len; i++)
    {
        key = sorted[i];
        if(logging > 1)
        {
            printf("\nkey: %ld\n", key);
            print_array("\tbefore:", sorted, len, i);
        }
        j = i - 1;
        // must use pre-incrementation because cmps start at 0
        if(logging > 1)
        {
            printf("\t\tcompare: %ld@[%0ld], %ld\n", sorted[j], j, key);
        }
        while (++r->count->cmps && j >= 0 && sorted[j] > key)
        {
            if(logging > 1)
            {
                printf("\t\t%ld > %ld, ", sorted[j], key);
                printf("pushing [%ld] -> [%ld]\n", j+1, j);
            }
            sorted[j+1] = sorted[j];
            r->count->swaps++;
            j--;
        }
        sorted[j+1] = key;
        r->count->swaps++;
        if(logging > 1)
        {
            print_array("\tafter:", sorted, len, i);
        }
    }
    r->array = sorted;
    return r;
}

Result *insert_sort_nocopy(long *array, long len, int logging, Result *r, int level)
{
    long key, j;
    for(long i=1; i < len; i++)
    {
        key = array[i];
        if(logging > 1)
        {
            indent(level);
            printf("key: %ld\n", key);
            indent(level);
            print_array("\tbefore:", array, len, i);
        }
        j = i - 1;
        // must use pre-incrementation because cmps start at 0
        if(logging > 1)
        {
            indent(level);
            printf("\t\tcompare: %ld@[%0ld], %ld\n", array[j], j, key);
        }
        while (++r->count->cmps && j >= 0 && array[j] > key)
        {
            if(logging > 1)
            {
                indent(level);
                printf("\t\t%ld > %ld, ", array[j], key);
                printf("pushing [%ld] -> [%ld]\n", j+1, j);
            }
            array[j+1] = array[j];
            r->count->swaps++;
            j--;
        }
        array[j+1] = key;
        r->count->swaps++;
        if(logging > 1)
        {
            indent(level);
            print_array("\tafter:", array, len, i);
        }
    }

    return r;
}
