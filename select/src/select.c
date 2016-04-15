#include "select.h"
SelectResult *select_result(){
    SelectResult *sr = malloc(sizeof(SelectResult));
    sr->nth=0;
    sr->cmps=0;
    return sr;
}



//--------------
// RANDOM SELECT
//==============

SelectResult *_random_select_nth(long *array, long start, long n, long end,
    SelectResult *sr, int logging, int depth);

SelectResult *random_select_nth(long *array, long len, long n, int logging)
{
    SelectResult *sr = select_result();
    sr = _random_select_nth(array, 0, n, len-1,sr,logging,0);
    return sr;
}

SelectResult *_random_select_nth(long *array, long start, long n, long end,
    SelectResult *sr, int logging, int depth)
{
        if(start == end) {
            sr->nth = array[start];
            return sr;
        }
        if(logging > 1)
        {
            indent(depth);
            print_array_range("before partition:", array, start, end, NO_SPECIAL);
        }
        long pidx = partition_hoare(array, start, end, PIVOT_RAND, &(sr->cmps),
                                    logging, depth);
        if(logging > 1)
        {
            indent(depth);
            print_array_range("after partition:", array, start, end, pidx);
        }
        long k = pidx - start + 1;
        if (++sr->cmps && n <= k) {
            return _random_select_nth(array, start, n, pidx, sr,logging,depth+1);
        }
        else {
            return _random_select_nth(array, pidx+1, n-k, end,sr,logging,depth+1);
        }
}

// Hoare's partition for random select
// Splits array[start...end] into 2 parts:
// [start..i] - elements lesser than pivot
// [j..end] - greater than pivot
long partition_hoare(long *array, long start, long end, long pivot, long *cmps,
    int logging, int depth)
{
    long x;
    if(pivot < 0) {
        x = array[rand()%end+start];
    }
    else {
        x = array[pivot];
    }


    if(logging > 1)
    {
        indent(depth);
        printf("pivot: %ld\n",x);
    }
    long i = start - 1;
    long j = end + 1;
    long tmp;
    while(1)
    {
        do {
            j--;
        } while(++*cmps && array[j] > x);
        do {
            i++;
        } while(++*cmps && array[i] < x);
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
