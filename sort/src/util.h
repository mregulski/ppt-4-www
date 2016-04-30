#ifndef UTIL
#define UTIL 1
#define DEBUG 1000
#define NO_SPECIAL -1


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    long swaps;
    long cmps;
} Counter;

Counter *counter();

typedef struct {
    Counter *count;
    long *array;
} Result;

Result *result();

typedef enum {
    Ascending,
    Descending,
    Random
} OrderingE;

long indexOf(long key, long *array, long len);

// fancy printers
void print_result(Result *r, long len, long time, int tabular, FILE *out);
void print_array(char *str, long *array, long len, long special_idx);
void print_array_range(char *str, long *array, long start, long stop, long special_idx);
void print_key(char *str, long *array, long len, long key_idx);
void indent(int level);

#endif
