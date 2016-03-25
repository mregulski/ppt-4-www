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
