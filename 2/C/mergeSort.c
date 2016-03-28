#include "util.h"
#include <string.h>

Result *_merge_sort(long *array, long len, Result *r, int logging);
Result *merge(long *left, long left_len, long *right,
              long right_len, long *array, Result *r, int logging);
Result *merge_sort(long *array, long len, int logging)
{
    long *copy = malloc(len * sizeof(long));
    memcpy(copy, array, len * sizeof(long));
    // if(logging > 0)
    // {
    //     printf("\nmerge sort\n");
    // }
    if(logging > 1)
    {
        print_array("array:", array, len);
        print_array(" copy:", copy, len);
    }
    Result *r = result();
    r = _merge_sort(copy, len, r, logging);
    r->array = copy;
    return r;
}

Result *_merge_sort(long *array, long len, Result *r, int logging)
{
    long *l_half, *r_half;
    long l_len, r_len;
    if (len < 2)
    {
        return r;
    }
    // lengths of halves
    l_len = len / 2;
    r_len = len - l_len;
    if(logging >= DEBUG)
    {
        printf("len: %ld, l_len: %ld, r_len: %ld\n",len,l_len,r_len);
    }
    l_half = malloc(l_len * sizeof(long));
    r_half = malloc(r_len * sizeof(long));

    //split array into halves
    for(int i = 0; i < l_len; i++)
    {
        l_half[i] = array[i];
        r->count->swaps++;
    }
    for(int i = 0; i < r_len; i++)
    {
        r_half[i] = array[i + l_len];
        r->count->swaps++;
    }
    if(logging > 1)
    {
        print_array("left: ", l_half, l_len);
        print_array("right:", r_half, r_len);
    }
    r = _merge_sort(l_half, l_len, r, logging);
    r = _merge_sort(r_half, r_len, r, logging);
    r = merge(l_half, l_len, r_half, r_len, array, r, logging);
    free(l_half);
    free(r_half);
    return r;
}

Result *merge(long *left, long left_len, long *right, long right_len,
              long *array, Result *r, int logging)
{
    long i = 0;
    long j = 0;
    long k = 0;
    if(logging >= DEBUG)
    {
        printf("left_len: %ld, right_len: %ld\n", left_len, right_len);
    }
    if(logging > 1)
    {
        print_array("merging:", left, left_len);
        print_array("   with:",     right, right_len);
    }
    while(i < left_len && j < right_len)
    {
        if(logging > 3)
        {
            printf("left[i=%ld]=%ld <=? right[j=%ld]=%ld\n", i, left[i], j, right[j]);
        }
        // !!!!!!!
        // super-important to use pre-incrementation (++x).
        // post-incrementation (x++) will prevent the first swap from occuring,
        // if it's occurence depends on the first swap
        if(++r->count->cmps && left[i] <= right[j])
        {
            if(logging > 2)
            {
                printf("left[i] > right[j], ");
                printf("appending left[%ld]=%ld\n", i, left[i]);
            }
            array[k] = left[i];
            i++;
        }
        else
        {
            if(logging > 2)
                printf("appending right[%ld] =%ld\n", j, right[j]);
            array[k] = right[j];
            j++;
        }
        // print_array("result so far: ", array, left_len+right_len);
        r->count->swaps++;
        k++;
    }
    // move remaining elements from left or right
    while(i < left_len)
    {
        if(logging > 2)
            printf(">appending left [%ld]\n", left[i]);
        array[k] = left[i];
        i++;
        k++;
        // r->count->swaps++;
    }

    while(j < right_len)
    {
        if(logging > 2)
            printf(">appending right [%ld]\n", right[j]);
        array[k] = right[j];
        j++;
        k++;
        // r->count->swaps++;
    }
    if(logging > 1)
    {
        print_array("->", array, left_len + right_len);
    }
    return r;
}
