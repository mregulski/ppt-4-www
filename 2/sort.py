#!/usr/bin/python3
import random
import sys
import getopt


def insert_sort(array, loggingEnabled):
    """insertion sort implementation with logging & operation counting"""
    for i in range(1, len(array)):
        key = array[i]
        j = i - 1
        while j >= 0 and array[j] > key:
            array[j+1] = array[j]
            j = j - 1
        array[j+1] = key
    return array


def merge_sort(array, loggingEnabled, level=0):
    """merge sort implementation with merge logging & operation counting"""
    if len(array) <= 1:
        return array

    left = []
    right = []
    for i in range(0, len(array)):
        if(i % 2 == 0):
            right.append(array[i])
        else:
            left.append(array[i])

    left = merge_sort(left, loggingEnabled, level + 1)
    right = merge_sort(right, loggingEnabled, level + 1)
    return merge(left, right, loggingEnabled, level)


def merge(left, right, loggingEnabled, level):
    result = []
    # disable logging for longer sublists
    if(loggingEnabled):  # and len(left) < 32 and len(right) < 32):
        print('{0:2d} {1} {2:8} {3}'
              .format(level, '--'*(level), 'merging:', left), sep=' ')
        print('{0:2} {1} {2:>8} {3}'
              .format('', "--"*(level), '&', right), sep=' ')
        # print(level + " ----"*(level-1) + " merging:   " + str(left))
        # print(level + " ----"*(level-1) + "         & " + str(right))
    while(len(left) > 0 and len(right) > 0):
        if(left[0] <= right[0]):
            result.append(left[0])
            left = left[1:]
        else:
            result.append(right[0])
            right = right[1:]
        # swaps++?
    # one of merged lists is empty now
    while(len(left) > 0):
        result.append(left[0])
        left = left[1:]
    while(len(right) > 0):
        result.append(right[0])
        right = right[1:]
    if(loggingEnabled):  # and len(result) < 64):
        print('{0:2} {1} {2:>8} {3}'
              .format('', '--'*(level), '->', result), sep=' ')
    #     print('{0:2d}' + '----'*(level-1) + '\t-> {1}', level, result)
    #     print(level + "----"*(level-1) + "\t-> " + str(result), end="\n\n")
    return result


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

    test_sort(listSize, merge_sort, loggingEnabled)

if __name__ == "__main__":
    main(sys.argv[1:])
