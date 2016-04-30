#include "util.h"
#include "sort.h"

// standalone version
Result *counting_sort(long *arr, long len, int logging)
{
    long *array = malloc(len * sizeof(long));
    memcpy(array, arr, len*sizeof(long));
    Result *r = result();
    int i;
    long min,max;
    min=max=array[0];
    for(i = 0; i < len; i++)
    {
        if(array[i] >= max) {
            max = array[i];
        }
        if(array[i] <= min) {
            min = array[i];
        }
    }
    if(logging > 1) {
        printf("max: %ld, min: %ld\n", max, min); }
    long range = max - min + 1;
    long *counts = malloc(range * sizeof(long));
    long *result = malloc((len) * sizeof(long));

    for(i = 0; i < range; i++)
    {
        counts[i] = 0;
    }

    for(i = 0; i < len; i++)
    {
        counts[array[i]-min]++;
    }
    if(logging > 1) {
        print_array("counts", counts, range, NO_SPECIAL); }
    for(i = 1; i < range; i++)
    {
        counts[i] += counts[i-1];
    }
    if(logging > 1) {
        print_array("counts", counts, range, NO_SPECIAL); }
    for(i = len-1; i >= 0; i--)
    {
        result[--counts[array[i]-min]] = array[i];
        r->count->swaps++;
    }
    free(counts);
    r->array = result;
    return r;
}

// for radix_sort. sorts by single digit,
Result *counting_sort_radix(long *array, long len, long base, long exp,
    Result *r, int logging)
{
    int i;
    long *counts = malloc(base * sizeof(long));
    long *result = malloc(len * sizeof(long));

    for(i = 0; i < base; i++)
    {
        counts[i] = 0;
    }

    for(i = 0; i < len; i++)
    {
        counts[(array[i]/exp)%base]++;
    }
    if(logging > 1) {
        print_array("individual counts:", counts, base, NO_SPECIAL);
    }
    for(i = 1; i < base; i++)
    {
        counts[i] += counts[i-1];
    }
    if(logging > 1) {
        print_array("prefix-summed counts", counts, base, NO_SPECIAL);
    }
    for(i = len-1; i >= 0; i--)
    {
        result[--counts[(array[i]/exp)%base]] = array[i];
        r->count->swaps++;
    }
    // if(logging > 1) {
    //     print_array("counting-sorted", result, len, NO_SPECIAL);
    // }
    free(counts);
    r->array = result;
    return r;
}
