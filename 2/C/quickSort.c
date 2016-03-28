#include "util.h"
#include <string.h>
#include <time.h>

Result *_quick_sort(long *array, long start, long stop, Result *r, int logging);

Result *quick_sort(long *array, long len, int logging)
{
    srand(time(NULL));
    long *copy = malloc(len * sizeof(long));
    memcpy(copy, array, len * sizeof(long));
    if(logging > 1)
    {
        print_array("arr:", array, len);
        print_array("cpy:", array, len);
    }
    Result *r = result();
    r->array = copy;
    r = _quick_sort(copy, 0, len-1, r, logging);
    return r;
}

Result *_quick_sort(long *array, long start, long stop, Result *r, int logging)
{
    if(logging > 2)
    {
        printf("\nsorting %ld through %ld\n", start, stop);
    }
    if (stop > start)
    {
        if(logging > 1)
        {
            print_array("before partition:", array, stop-start);
        }
        long pivot, pivot_idx, tmp, i, j;
        pivot_idx = start;
        pivot = array[pivot_idx];
        i = start - 1;
        j = stop + 1;
        while(1)
        {
            do {
                r->count->cmps++;
                i++;
            } while(array[i] < pivot);
            do {
                r->count->cmps++;
                j--;
            } while(array[j] > pivot);
            if (i >= j)
            {
                break; //ret j
            }
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            r->count->swaps++;
        }
        if(logging > 1)
        {
            printf("start: %ld, stop: %ld, pivot_idx: %ld, i: %ld\n",
                start, stop, pivot_idx, i);
            print_array("after partition:", array, stop-start);
        }
        r = _quick_sort(array, start, j, r, logging);
        r =  _quick_sort(array, j+1, stop, r, logging);
        return r;
    }
    return r;

}
