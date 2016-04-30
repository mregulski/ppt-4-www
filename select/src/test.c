// #include "../../sort/src/sort.h"
#include "../../sort/src/util.h"
#include "../../sort/src/sort.h"
#include "select.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
/*
    SELECT ALGORITHM:
        * RANDOM SELECT
        * SELECT
        * logging
    GENERATORS:
        * random
        * random permutation [1..n]
    PARAMS:
        * generator
        * size
        * max data
        * which stat

*/

typedef enum {
    Rand,
    Perm
} DataTypeE;

long *generate_data(long size, long max, DataTypeE type);
long *generate_data_random(long size, long max);
long *generate_data_perm(long size);


int main(int argc, char **argv) {
    /*
        parse argv
        generate data
        mark stat
        sort data
        check stat index
    */
    srand(time(0));
    // default settings
    long size = 9;
    long max = size;
    DataTypeE type = Rand;
    int logging = 5;
    long n = 5;

    /* parse argv */
    extern int opterr;
    opterr = 0;
    extern char *optarg;
    int c;
    do
    {
        // size, n, type, verbose, max(range)
        c = getopt(argc,argv,"s:n:t:m:v:");
        switch(c) {
            case 's':
                size = strtol(optarg, NULL, 10);
                break;
            case 'n':
                n = strtol(optarg, NULL, 10);
                break;
            case 't':
                if(strcmp(optarg, "perm") == 0) {
                    type = Perm;
                } else if(strcmp(optarg, "rand") == 0) {
                    type = Rand;
                }
                break;
            case 'm':
                max = strtol(optarg, NULL, 10);
                break;
            case 'v':
                logging = strtol(optarg, NULL, 10);
                break;
        }
    } while (c != -1);

    /* generate data */
    long *array = generate_data(size, max, type);
    if(logging > 0) /* 'interactive' mode */
    {
        long *copy = malloc(size * sizeof(long));
        memcpy(copy, array, size * sizeof(long));
        // random
        print_array("generated array:", copy, size, NO_SPECIAL);
        // long k = partition(copy, 0, size, 13, logging, 0);
        // printf("k=%ld\n",k);
        // print_array("partitioned array:", copy, size, NO_SPECIAL);
        long x = select_nth(copy, size, n, logging);
        printf("%ldth element: %ld\n",n,x);
        copy = quick_sort(copy, size, 0)->array;
        print_array("sorted:", copy, size, indexOf(x, copy, size));
        // printf("Looking for %ldth value\n", n);
        //
        // printf("> press ENTER to start median5 select.");
        // getchar();
        // long res = select_nth(copy, size, n, logging);
        // printf("%ldth value: %ld\n", n, res);
        // printf("> press ENTER to check.");
        // getchar();
        // copy = quick_sort(copy, size, 0)->array;
        // print_array("sorted:", copy, size, indexOf(res, copy, size));
        // printf("cmps: %ld\n", rnd->cmps);

        // printf("> press ENTER to start RandomSelect.");
        // getchar();
        // SelectResult *rnd = random_select_nth(copy, size, n, logging);
        // printf("%ldth value: %ld\n", n, rnd->nth);
        // printf("> press ENTER to check.");
        // getchar();
        // copy = quick_sort(copy, size, 0)->array;
        // print_array("sorted:", copy, size, indexOf(rnd->nth, copy, size));
        // printf("cmps: %ld\n", rnd->cmps);


    }



}

// wrapper for generating different data.
long *generate_data(long size, long max, DataTypeE type)
{
    long *array;
    switch(type)
    {
        case Rand:
            array = generate_data_random(size, max);
            break;
        case Perm:
            array = generate_data_perm(size);
            break;
        default:
            array = NULL;
            break;
    }
    return array;
}

// Generate array of {size} random elements from [0 .. {max}-1]
long *generate_data_random(long size, long max) {
    long *array = malloc(size * sizeof(long));
    for(int i = 0; i < size; i++)
    {
        array[i] = rand()%(max*4);
    }
    return array;
}

// Generate a random permutation of [1..{size}]
long *generate_data_perm(long size)
{
    long *array = malloc(size * sizeof(long));
    long *used = malloc(size * sizeof(long));
    memset(used, 0, size*sizeof(long));
    long val;
    for(int i = 0; i < size; i++)
    {
        do
        {
            val = rand()%size + 1;
            array[i] = val;
        } while(used[val-1] == 1);
        used[val-1] = 1;
    }
    return array;
}
