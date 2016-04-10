#ifndef QUICK
#define QUICK 1
#include "util.h"
#include <string.h>
#include <time.h>

Result *_quick_sort(long *array, long start, long stop, Result *r, int threshold,  int logging, int level);

Result *quick_sort(long *array, long len, int logging)
{
    srand(time(NULL));
    long *copy = malloc(len * sizeof(long));
    memcpy(copy, array, len * sizeof(long));
    if(logging > 1)
    {
        print_array("arr:", array, len, NO_SPECIAL);
        print_array("cpy:", array, len, NO_SPECIAL);
        printf("start\n\n");
    }
    Result *r = result();
    r->array = copy;
    r = _quick_sort(copy, 0, len-1, r, 0, logging, 0);
    return r;
}

Result *_quick_sort(long *array, long start, long stop, Result *r, int threshold, int logging, int level)
{
    if(logging > 2)
    {
        printf("\nsorting %ld through %ld\n", start, stop);
    }
    if (stop - start > threshold)
    {
        long pivot, pivot_idx, tmp, i, j;
        //pivot_idx = start;
        pivot_idx = rand()%(stop-start+1) + start;
        pivot = array[pivot_idx];
        if(logging > 1)
        {
            indent(level);
            print_array_range("partitioning:", array, start, stop, pivot_idx);
            indent(level);
            printf("pivot: array[%ld] = %ld\n", pivot_idx, pivot);
        }
        // Hoare's partitioning
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
                if(logging > 1)
                {
                    indent(level);
                    printf("pointers crossed: i = %ld, <j = %ld>\n",i,j);
                }
                break; //ret j
            }
            if (logging > 1)
            {
                indent(level);
                printf("swapping %ld @ [%ld] with %ld @ [%ld]\n", array[i], i, array[j], j);
            }
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            r->count->swaps++;
        }
        if(logging > 1)
        {
            // indent(level);
            // printf("start: %ld, stop: %ld, pivot_idx: %ld, i: %ld\n",
            //     start, stop, pivot_idx, i);
            indent(level);
            print_array_range("after partition:", array, start, stop, NO_SPECIAL);
        }
        r = _quick_sort(array, start, j, r, threshold, logging, level+1);
        return  _quick_sort(array, j+1, stop, r, threshold, logging, level+1);
        //return r;
    }
    return r;

}
#endif
