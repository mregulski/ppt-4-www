#include "select.h"

static long cmps = 0;
static long ARRAY_SIZE = 0;
long _select_nth(long *array, long left, long right, long n, int logging,int depth);

// long _select_nth(long *array, long left, long right, long n);
// long pivot(long *array, long left, long right);
// long partition(long *array, long left, long right, long pivot_idx);
// long median(long *array, long left, long right);
//
long select_nth(long *array, long len, long n, int logging)
{
    ARRAY_SIZE = len;
    return _select_nth(array, 0, len, n, logging, 0);
}


void partial_insert_sort(long *array, long left, long right)
{
    long key, j;
    for(long i = left; i <= right; i++)
    {
        key = array[i];
        j = i - 1;

        while (++cmps && j >= 0 && array[j] > key && j>=left)
        {
            array[j+1] = array[ j];
            j--;
        }
        array[j+1] = key;
    }
}
// sort array[left,right] and retirn middle element
// (higher of two middle ones if range's length is even).
// STATUS: OK
long median(long *array, long left, long right, int depth)
{
    partial_insert_sort(array, left, right);
    indent(depth);
    print_array("[MEDIAN] array:", array, ARRAY_SIZE, NO_SPECIAL);
    indent(depth);
    printf("[MEDIAN] slice [%ld, %ld]:",left, right);
    indent(depth);
    print_array_range("", array, left, right, NO_SPECIAL);
    long median, median_i;
    if((right-left)%2 == 0) {
        median_i = (right+left)/2; }
    else  {
        median_i = (right+left)/2+1; }
    median = array[median_i];
    indent(depth);
    printf("[MEDIAN] median: \e[1;32m%ld\e[0m (array[%ld])\n", median, median_i);
    return median;
}

long _select_nth(long *array, long left, long right, long n, int logging, int depth)
{
    if(right-left < 10)
    {
        indent(depth);
        printf("[_SELECT] range [%ld, %ld] < 10.\n",left,right);
        partial_insert_sort(array, left, right);
        indent(depth);
        printf("[_SELECT] returning %ldth element: %ld\n",n, array[n]);
        indent(depth);
        print_array_range("from:", array, left,right,n);
        return array[n];
    }
    long g_right,m=0;
    if(logging > 1)
    {
        indent(depth);
        printf("[_SELECT] size: %ld\n", right-left);
    }
    long num_medians = (right-left)%5 == 0 ? (right-left)/5 : (right-left)/5 + 1;
    long *medians = malloc(num_medians * sizeof(long));
    if(logging > 1)
    {
        indent(depth);
        printf("[_SELECT] medians.len = %ld\n", num_medians);
    }
    for(int i = left; i < right; i += 5)
    {
        g_right = i + 4;
        if(g_right >= right) { g_right = right-1; }
        if(logging > 1)
        {
            indent(depth);
            printf("[_SELECT] i: %d, g_right: %ld\n", i, g_right);
        }
        medians[m] = median(array,i,g_right, depth+1);
        m++;
    }
    indent(depth);
    print_array("\e[1;32m[_SELECT] medians: ", medians, num_medians, NO_SPECIAL);
    printf("\e[0m");
    // ARRAY_SIZE = num_medians;
    long m_of_m = _select_nth(medians, 0, num_medians, num_medians/2, logging, depth+1);
    long k = partition(array,left,right, m_of_m, logging, 1) + 1;
    indent(depth);
    printf("[_SELECT] partition by: %ld. k=%ld\n",m_of_m,k);
    indent(depth);
    print_array_range("[_SELECT] partitioned: ", array, left, right, NO_SPECIAL);
    if(n <= k) {
        indent(depth);
        printf("looking for %ldth element in: ", n);
        print_array_range("", array, left, k-1, NO_SPECIAL);
        return _select_nth(array, left, k-1, n, logging, depth+1);
    }
    else {
        indent(depth);
        printf("looking for %ldth element in: ", n-k);
        print_array_range("", array, k, n-k, NO_SPECIAL);
        return _select_nth(array, k, right, n-k, logging, depth+1);
    }
}


long partition(long *array, long start, long end, long pivot, int logging,
     int depth)
{
    long x = pivot;
    if(logging > 1)
    {
        indent(depth);
        printf("[PARTITION] pivot: %ld\n",x);
    }
    long i = start - 1;
    long j = end + 1;
    long tmp;
    while(1)
    {
        do {
            j--;
        } while(++cmps && array[j] > x);
        do {
            i++;
        } while(++cmps && array[i] < x);
        if(i < j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
        else
        {
            return j;
        }
    }
}
