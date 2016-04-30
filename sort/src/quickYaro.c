#include "util.h"
#include "sort.h"

// main sorting function


// launcher function
Result *yaro_quick_sort(long *array, long len, int logging)
{
    long *copy = malloc(len * sizeof(long));
    memcpy(copy, array, len * sizeof(long));
    if(logging > 1)
    {
        print_array("arr:", array, len, NO_SPECIAL);
        print_array("cpy:", array, len, NO_SPECIAL);
    }
    Result *r = result();
    r->array = copy;
    r = _yaro_quick_sort(copy, 0, len-1, r, logging);
    //r = insert_sort_nocopy(copy, len, logging, r);
    return r;
}
//
// NOT WORKING CORRECTLY
//
Result *_yaro_quick_sort(long *array, long start, long stop, Result *r, int logging)
{
        if(stop - start < 2)
        {
            return r;
        }
        long left_idx = start;//rand()%(stop-start+1) + start;
        long right_idx = stop;//rand()%(stop-start+1) + start;
        long tmp;

        long left_pvt = array[left_idx], right_pvt = array[right_idx];
        if(array[left_idx] < array[right_idx] && start > stop)
        {
            printf("swapping pivots(%ld <> %ld)\n", left_pvt, right_pvt);
            tmp = left_idx;
            left_idx = right_idx;
            right_idx = tmp;
        }

        long a = start+1, k = a, b = stop-1;
        if(logging > 1)
        {
            printf("\na: %ld, b: %ld, k: %ld\nleft pivot: %ld, right pivot: %ld | start: %ld, stop: %ld\n",
                    a, b, k, left_pvt, right_pvt, start, stop);
        }
        while(k <= b)
        {
            if(++r->count->cmps && array[k] < left_pvt)
            {
                if(logging > 1)
                {
                    printf("\t%ld@%ld < left pivot = %ld\n", array[k],k, left_pvt);
                    printf("\t\tswapping %ld@%ld <> %ld@%ld\n", array[k], k, array[a],a );
                }
                tmp = array[k];
                array[k] = array[a];
                array[a] = tmp;
                r->count->swaps++;
                a++;
            }
            else
            {
                if(++r->count->cmps && array[k] > right_pvt)
                {
                    while(++r->count->cmps && array[b] > right_pvt && k < b)
                    {
                        b--;
                    }
                    if(logging > 1)
                    {
                        printf("\t%ld%ld > right pivot = %ld\n", array[k], k, right_pvt);
                        printf("\t\tswapping %ld <> %ld\n", array[k], array[b]);
                    }
                    tmp = array[k];
                    array[k] = array[b];
                    array[b] = tmp;
                    r->count->swaps++;
                    b--;
                    if(++r->count->cmps && array[k] < left_pvt)
                    {
                        if(logging > 1)
                        {
                            printf("\t%ld%ld < left pivot = %ld\n", array[k], k, left_pvt);
                            printf("\t\tswapping %ld <> %ld\n", array[k], array[a]);
                        }
                        tmp = array[k];
                        array[k] = array[a];
                        array[a] = tmp;
                        r->count->swaps++;
                        a++;
                    }
                }
            }
            k++;
        }
        a--;
        b++;
        if(logging > 1)
        {
            printf("\tswapping %ld <> %ld ([%ld]<>[%ld])\n", array[start], array[a],start,a);
        }
        tmp = array[start];
        array[start] = array[a];
        array[a] = tmp;
        if(logging > 1)
        {
            printf("\tswapping %ld <> %ld\n", array[stop], array[b]);
        }
        tmp = array[stop];
        array[stop] = array[b];
        array[b] = tmp;
        r->count->swaps += 2;
        r = _yaro_quick_sort(array, start, a, r, logging);
        r = _yaro_quick_sort(array, a+1, b, r, logging);
        return _yaro_quick_sort(array, b+1, stop, r, logging);

}
