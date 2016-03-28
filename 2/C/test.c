#include "util.h"
#include "insertSort.c"
#include "mergeSort.c"
#include "quickSort.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// generators
long *generate_list_random(long size);
long *generate_list_ascending(long size);
long *generate_list_descending(long size);

// main test method
void test(long test_size, int logging, OrderingE list_type);

int main(int argc, char **argv)
{
    long test_size = 30;
    int logging = 0;
    OrderingE list_type = Random;
    opterr = 0;
    int c;

    // parse command line options
    do
    {
        c = getopt(argc,argv,"s:t:v");
        switch (c)
        {
            case 's':
                test_size = strtol(optarg, NULL,10);
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
                logging++;
                break;
        }
    } while(c != -1);

    // run tests
    test(test_size, logging, list_type);
    // long a[5] = {8,4,6,3,1};
    // long b[5] = {7,2,5,9,0};
    // long d[10] = {0};
    // Result *r = merge(a,5,b,5,d, NULL, 0);


}


void test(long test_size, int logging, OrderingE list_type)
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
    if(logging > 1)
    {
        print_array("Generated array:", arr, test_size);
    }

    int tabular_out = logging == 0 ? 1 : 0;

    if(tabular_out)
    {
        printf("%13s\t%7s\t%12s\t%12s\n","","size","swaps","comparisons");
    }
    // enable full logging
    // logging = DEBUG;

    printf("insert sort:\t");
    // print_array("\nbefore", arr, test_size);
    Result *insert = insert_sort(arr, test_size, logging);
    if(logging > 0)
    {
        print_array(NULL, insert->array, test_size);
    }
    print_result(insert, test_size, tabular_out);

    printf("merge sort:\t");
    // print_array("\nbefore:", arr, test_size);
    Result *merge = merge_sort(arr, test_size, logging);
    if(logging > 0)
    {
        print_array(" after:", merge->array, test_size);
    }
    print_result(merge, test_size, tabular_out);

    printf("quick sort:\t");
    // print_array("\nbefore", arr, test_size);
    Result *quick = quick_sort(arr, test_size, logging);
    if(logging > 0)
    {
        print_array(NULL, quick->array, test_size);
    }
    print_result(quick, test_size, tabular_out);
}

long *generate_list_random(long size)
{
    srand(time(NULL));
    long *arr = malloc(sizeof(long) * size);
    for(long i = 0; i < size; i++)
    {
        arr[i] = rand()%(size*4);
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
