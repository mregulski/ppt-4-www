#include "util.h"
#include "sort.h"

// requires knowing array's maximum (maxVal)
Result *counting_sort(long *array, long len, long maxVal, int logging)
{
    Result *r = result();
    long *counts = calloc(maxVal, sizeof(long));
    long *result = calloc(len, sizeof(long));
    long total = 0, oldCount = 0;
    int j;
    for(j = 0; j < len; j++)
    {
        counts[array[j]]++;
    }
    for(j = 1; j < maxVal; j++)
    {
        counts[j] += counts[j-1];
    }
    for(j = len-1; j >= 0; j--)
    {
        result[counts[array[j]]] = array[j];
        counts[array[j]]--;
    }
    r->array = result;
    return r;
}
