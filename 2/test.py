#!/usr/bin/python3
import random
import sys
import getopt
from sort import quickSort, mergeSort, insertSort


def generate_list_rand(size):
    array = []
    for i in range(0, size):
        array.append(random.SystemRandom().randint(1, size*10))
    return array


def generate_list_desc(size):
    array = []
    for i in range(size, 0, -1):
        array.append(i)
    return array


def generate_list_asc(size):
    array = []
    for i in range(0, size):
        array.append(i)
    return array


def test_sort(array, sortFn, loggingEnabled):
    if loggingEnabled > 0:
        print(sortFn.__name__ + ": ")
        print("-> {}{}".format(array[0:32], '...' if len(array) > 32 else ''))
    array_sorted, swaps, compares = sortFn(array,
                                           loggingEnabled=loggingEnabled)
    if loggingEnabled > 0:
        print("\n<- {}{}".format(array_sorted[0:32],
                                 '...' if len(array) > 32 else ''))
        print("----------")
    print('[{}] swaps: {:10d} | comparisons: {:10d} | total: {:11d}'
          .format(sortFn.__name__, swaps, compares, swaps + compares))
    print("-" * 40)


def main(argv):
    usageMsg = 'sort.py -s <size> [-t <random|desc>][-v]'
    loggingEnabled = 0
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
            loggingEnabled += 1
        elif opt == '-s':
            listSize = int(arg)
        elif opt == '-t':
            if arg == 'desc':
                testList = generate_list_desc(listSize)
            elif arg == 'random':
                testList = generate_list_rand(listSize)
            elif arg == 'asc':
                testList = generate_list_asc(listSize)
            else:
                print(usageMsg)
                sys.exit(2)
    # testList = [0, 2, 4, 6, 1, 3, 5, 7]
    if loggingEnabled > 0:
        print("test list: {}\n".format(testList))
    # test_sort(testList, insertSort.insert_sort, loggingEnabled)
    test_sort(testList, mergeSort.merge_sort, loggingEnabled)
    test_sort(testList, quickSort.quick_sort, loggingEnabled)


if __name__ == "__main__":
    main(sys.argv[1:])
