#include "util.h"
#include <string.h>

Result *insert_sort(long *array, long len, int logging)
{
    Result *r = result();
    // work on a copy, to allow reuse of array in multiple tests
    long *sorted = malloc(sizeof(long)*len);
    sorted = memcpy(sorted, array, sizeof(long)*len);

    long key, j;
    for(long i=0; i < len; i++)
    {
        key = sorted[i];
        if(logging > 1)
        {
            printf("key: %ld\n", key);
            print_array("before:", sorted, len);
        }
        j = i - 1;
        // must use pre-incrementation.
        // explanation in mergeSort.c:merge
        while (++r->count->cmps && j >= 0 && sorted[j] > key)
        {
            sorted[j+1] = sorted[j];
            r->count->swaps++;
            j--;
        }
        sorted[j+1] = key;
        r->count->swaps++;
        if(logging > 1)
        {
            print_array("after:", sorted, len);
        }
    }
    r->array = sorted;
    return r;
}
