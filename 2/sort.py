#!/usr/bin/python3
import random
import sys
import getopt
from sort import mergeSort, insertSort, quickSort


def generate_list(size):
    array = []
    for i in range(0, size):
        array.append(random.SystemRandom().randint(1, size*10))
    return array


def test_sort(list_size, sort_fn, loggingEnabled):
    print(sort_fn.__name__ + ": ")
    x = generate_list(list_size)
    print("-> " + str(x[:64]))
    x_sorted = sort_fn(x, loggingEnabled)
    print("\n<- " + str(x_sorted[:64]))
    print("----------")
    print()


def main(argv):
    usageMsg = 'sort.py -s <size> [-t <random|desc>][-v]'
    loggingEnabled = False
    listType = 'random'
    listSize = 16
    try:
        opts, args = getopt.getopt(argv, "vs:t:")
    except getopt.GetoptError:
        print(usageMsg)
        sys.exit(2)
    if len(opts) == 0:
        print(usageMsg)
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-v':
            loggingEnabled = True
        elif opt == '-s':
            listSize = int(arg)
        elif opt == '-t':
            if arg == 'desc':
                listType = 'descending'
            elif arg == 'random':
                listType = 'random'
            else:
                print(usageMsg)
                sys.exit(2)

    test_sort(listSize, mergeSort.merge_sort, loggingEnabled)

if __name__ == "__main__":
    main(sys.argv[1:])
