#include "util.h"
#include "insertSort.c"
#include "mergeSort.c"
#include "quickSort.c"
#include "quickHybrid.c"
#include "mergeInsert.c"
#include "quickYaro.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// generators
long *generate_list_random(long size);
long *generate_list_ascending(long size);
long *generate_list_descending(long size);

struct flags {
    int insert;
    int merge;
    int quick;
    int qi;
    int mi;
    int yaro;
};

// main test method
void test(long test_size, int logging, OrderingE list_type, int qi_threshold, int qm_threshold, struct flags filter);



// launcher
int main(int argc, char **argv)
{
    // DEFAULT SETTINGS

    // length of test list
    long test_size = 30;
    // how many details are logged
    int logging = 0;
    // array length at which quick_insert switches from quick to insert sort
    int qi_threshold = 30;
    // array length at which quick_insert switches from quick to merge sort
    int qm_threshold = 30;
    // type of list to generate
    OrderingE list_type = Random;
    // sort flags
    int filter = 0;
    struct flags filterRules = {1,1,1,1,1,1};



    // parse command line options
    opterr = 0;
    int c;
    do
    {
        c = getopt(argc,argv,"s:t:v:i:m:fABCDEF");
        switch (c)
        {
            case 's':
                test_size = strtol(optarg, NULL, 10);
                break;
            case 't':
                if (strcmp(optarg, "asc") == 0
                    || strcmp(optarg, "ascending") == 0)
                    {
                        list_type = Ascending;
                    }
                else if (strcmp(optarg, "desc") == 0
                         || strcmp(optarg, "descending") == 0)
                         {
                             list_type = Descending;
                         }
                else
                {
                    list_type = Random;
                }
                break;
            case 'v':
                logging = (int)strtol(optarg, NULL, 10);
                break;
            case 'i':
                qi_threshold = (int)strtol(optarg, NULL, 10);
                break;
            case 'm':
                qm_threshold = (int)strtol(optarg, NULL, 10);
                break;
            case 'f':
                filter = 1;
                filterRules.insert=filterRules.merge=filterRules.quick = 0;
                filterRules.qi=filterRules.mi=filterRules.yaro = 0;
                break;
            case 'A':
                filterRules.insert=1;
                break;
            case 'B':
                filterRules.merge=1;
                break;
            case 'C':
                filterRules.quick=1;
                break;
            case 'D':
                filterRules.qi=1;
                break;
            case 'E':
                filterRules.mi=1;
                break;
            case 'F':
                filterRules.yaro=1;
                break;
        }
    } while(c != -1);

    if (filter)
    {

    }
    // run tests
    test(test_size, logging, list_type, qi_threshold, qm_threshold, filterRules);
    // long a[5] = {8,4,6,3,1};
    // long b[5] = {7,2,5,9,0};
    // long d[10] = {0};
    // Result *r = merge(a,5,b,5,d, NULL, 0);


}

// cut-off value for printing sorted arrays
#define MAX_OUTPUT_ARRAY 32
void test(long test_size, int logging, OrderingE list_type, int qi_threshold, int qm_threshold, struct flags filter)
{
    long *arr = NULL;
    switch (list_type)
    {
        case Ascending:
            arr = generate_list_ascending(test_size);
            if(logging > 1)
            {
                printf("Generating scending list of size %ld.\n", test_size);
            }
            break;
        case Descending:
            arr = generate_list_descending(test_size);
            if(logging > 1)
            {
                printf("Generating descending list of size %ld.\n", test_size);
            }
            break;
        case Random:
            arr = generate_list_random(test_size);
            if(logging > 1)
            {
                printf("Generating random list of size %ld.\n", test_size);
            }
            break;
    }
    if(logging > 0)
    {
        print_array("Generated array:", arr, test_size, NO_SPECIAL);
    }

    int tabular_out = logging == 0 ? 1 : 0;

    // if(tabular_out)
    // {
    //     printf("%13s\t%7s\t%12s\t%12s\n","","size","swaps","comparisons");
    // }
    // enable full logging
    // logging = DEBUG;

    clock_t start, stop;
    if(filter.insert)
    {
        printf("%-15s","insert sort:\n");
        // print_array("\nbefore", arr, test_size);
        start=clock();
        Result *insert = insert_sort(arr, test_size, logging);
        stop = clock();
        if(logging > 0 && test_size < MAX_OUTPUT_ARRAY)
        {
            print_array("\nsorted:", insert->array, test_size, NO_SPECIAL);
        }
        print_result(insert, test_size, stop-start, tabular_out);
    }
    if(filter.merge)
    {
        printf("%-15s", "merge sort:\n");
        // print_array("\nbefore:", arr, test_size);
        start = clock();
        Result *merge = merge_sort(arr, test_size, logging);
        stop = clock();
        if(logging > 0 && test_size < MAX_OUTPUT_ARRAY)
        {
            print_array("\nsorted:", merge->array, test_size, NO_SPECIAL);
        }
        print_result(merge, test_size, stop-start, tabular_out);
    }
    if(filter.quick)
    {
        printf("%-15s", "quick sort:\n");
        // print_array("\nbefore:", arr, test_size);
        start = clock();
        Result *quick = quick_sort(arr, test_size, logging);
        stop = clock();
        if(logging > 0 && test_size < MAX_OUTPUT_ARRAY)
        {
            print_array("\nsorted:", quick->array, test_size, NO_SPECIAL);
        }
        print_result(quick, test_size, stop-start, tabular_out);
    }
    if(filter.qi)
    {
        printf("%-15s","quick+insert:\n");
        // print_array("\nbefore", arr, test_size);
        start = clock();
        Result *quick_insert = quick_insert_sort(arr, test_size, logging, qi_threshold);
        stop = clock();
        if(logging > 0 && test_size < MAX_OUTPUT_ARRAY)
        {
            print_array("\nsorted:", quick_insert->array, test_size, NO_SPECIAL);
        }
        print_result(quick_insert, test_size, stop-start, tabular_out);
    }
    if(filter.mi)
    {
        printf("%-15s","merge+insert:\n");
        start = clock();
        Result *merge_insert = merge_insert_sort(arr, test_size, qm_threshold, logging);
        stop = clock();
        if(logging > 0 && test_size < MAX_OUTPUT_ARRAY)
        {
            print_array("\nsorted", merge_insert->array, test_size, NO_SPECIAL);
        }
        print_result(merge_insert, test_size, stop-start, tabular_out);
    }
    // makes no sense
    // printf("%-15s","quick+merge:");
    // // print_array("\nbefore", arr, test_size);
    // Result *quick_merge = quick_merge_sort(arr, test_size, qm_threshold, logging);
    // if(logging > 0 && test_size < MAX_OUTPUT_ARRAY)
    // {
    //     print_array("\nsorted", quick_merge->array, test_size);
    // }
    // print_result(quick_merge, test_size, stop-start, tabular_out);

    //doenst workd
    if(filter.yaro)
    {
        printf("%-15s","Yaroslavskiy:\n");
        print_array("\nbefore", arr, test_size, NO_SPECIAL);
        start = clock();
        Result *yaro = yaro_quick_sort(arr, test_size, logging);
        stop = clock();
        if(logging > -1 && test_size < MAX_OUTPUT_ARRAY)
        {
            print_array("\nsorted", yaro->array, test_size, NO_SPECIAL);
        }
        print_result(yaro, test_size, stop-start, tabular_out);
    }
}

long *generate_list_random(long size)
{
    srand(time(NULL));
    long *arr = malloc(sizeof(long) * size);
    for(long i = 0; i < size; i++)
    {
        arr[i] = rand()%(size*2);
    }
    return arr;
}

long *generate_list_ascending(long size)
{
    long *arr = malloc(sizeof(long) * size);
    for(long i = 0; i < size; i++)
    {
        arr[i] = i;
    }
    return arr;
}

long *generate_list_descending(long size)
{
    long *arr = malloc(sizeof(long) * size);
    for(long i = 0; i < size; i++)
    {
        arr[i] = size-i;
    }
    return arr;
}
