#ifndef SORT
#define SORT 1
#include "util.h"
// INSERTION SORT
Result *insert_sort(long *array, long len, int logging);
Result *insert_sort_nocopy(long *array, long len, int logging, Result *r,
                           int level);

// MERGE SORT
Result *merge_sort(long *array, long len, int logging);
Result *_merge_sort(long *array, long len, Result *r, int logging, int level);
Result *merge(long *left, long left_len, long *right,
              long right_len, long *array, Result *r, int logging, int level);

// QUICK SORT
Result *_quick_sort(long *array, long start, long stop, Result *r,
                    int threshold,  int logging, int level);
Result *quick_sort(long *array, long len, int logging);

// MERGE + INSERT
Result *_merge_insert_sort(long *array, long len, Result *r, int threshold,
                           int logging, int level);
Result *merge_insert_sort(long *array, long len, int threshold, int logging);

// QUICK + INSERT
Result *quick_insert_sort(long *array, long len, int logging, int threshold);

// DOUBLE PIVOT QUICK SORT (Yaroslavskiy)
Result *yaro_quick_sort(long *array, long len, int logging);
Result *_yaro_quick_sort(long *array, long start, long stop, Result *r,
    int logging);

// COUNTING SORT
Result *counting_sort(long *array, long len, int logging);
Result *counting_sort_radix(long *array, long len, long base, long exp,
    Result *r, int logging);
// RADIX SORT
Result *radix_sort(long *array, long len, int base, int logging);
#endif
