#include "util.h"
#include "insertSort.c"
#include "mergeSort.c"
#include "quickSort.c"
#include <string.h>
#include <time.h>

// Result *_quick_insert_sort(long *array, long start, long stop, Result *r, int logging, int threshold);
//
// Result *quick_insert_sort2(long *array, long len, int logging, int threshold)
// {
//     srand(time(NULL));
//     long *copy = malloc(len * sizeof(long));
//     memcpy(copy, array, len * sizeof(long));
//     if(logging > 1)
//     {
//         print_array("arr:", array, len);
//         print_array("cpy:", array, len);
//     }
//     Result *r = result();
//     r->array = copy;
//     r = _quick_insert_sort(copy, 0, len-1, r, logging, threshold);
//     return r;
// }

Result *quick_insert_sort(long *array, long len, int logging, int threshold)
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
    r = _quick_sort(copy, 0, len-1, r, threshold, logging);
    if(logging > 1)
    {
        print_array("\nquicksort done: ", copy, len);
    }
    return insert_sort_nocopy(copy, len, logging, r);

}

Result *quick_merge_sort(long *array, long len, int threshold, int logging)
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
    r = _quick_sort(copy, 0, len-1, r, threshold, logging);
    if(logging > 1)
    {
        print_array("\nquicksort done: ", copy, len);
    }
    return _merge_sort(copy, len, r, logging);

}


// Result *_quick_insert_sort(long *array, long start, long stop, Result *r, int logging, int threshold)
// {
//     if(logging > 2)
//     {
//         printf("\nsorting %ld through %ld\n", start, stop);
//     }
//     if (stop > start)
//     {
//         if(stop - start < threshold)
//         {
//             return insert_sort_nocopy(array, stop-start+1, logging, r);
//             //return r;
//         }
//         if(logging > 1 && stop-start < 10)
//         {
//             print_array("before partition:", array, stop-start);
//         }
//         long pivot, pivot_idx, tmp, i, j;
//         //pivot_idx = start;
//         pivot_idx = rand()%(stop-start+1) + start;
//         pivot = array[pivot_idx];
//         i = start - 1;
//         j = stop + 1;
//         while(1)
//         {
//             do {
//                 r->count->cmps++;
//                 i++;
//             } while(array[i] < pivot);
//             do {
//                 r->count->cmps++;
//                 j--;
//             } while(array[j] > pivot);
//             if (i >= j)
//             {
//                 break; //ret j
//             }
//             tmp = array[i];
//             array[i] = array[j];
//             array[j] = tmp;
//             r->count->swaps++;
//         }
//         if(logging > 1 && stop-start < 10)
//         {
//             printf("start: %ld, stop: %ld, pivot_idx: %ld, i: %ld\n",
//                 start, stop, pivot_idx, i);
//             print_array("after partition:", array, stop-start);
//         }
//         r = _quick_insert_sort(array, start, j, r, logging, threshold);
//         return  _quick_insert_sort(array, j+1, stop, r, logging, threshold);
//         //return r;
//     }
//     return r;
//
// }
