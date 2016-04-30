#ifndef SELECT
#define SELECT 1
#include "../../sort/src/util.h"
#include "../../sort/src/sort.h"
typedef struct {
    long nth;
    long cmps;
} SelectResult;

typedef struct {
    long val;
    long cmps;
} GenResult;

long select_nth(long *array, long len, long n, int logging);
long partition(long *array, long start, long end, long pivot, int logging,
     int depth);
SelectResult *select_result();
SelectResult *random_select_nth(long *array, long len, long n, int logging);
#define PIVOT_RAND -1
long partition_hoare(long *array, long start, long end, long pivot, long *cmps,
    int logging, int depth);

long median(long *array, long left, long right, int depth);

#endif
