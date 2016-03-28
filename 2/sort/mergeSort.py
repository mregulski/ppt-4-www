def merge_sort(array, loggingEnabled, level=0, swaps=0, cmp=0):
    """merge sort implementation with merge logging & operation counting"""
    if len(array) <= 1:
        return array, swaps, cmp

    left = []
    right = []
    for i in range(0, len(array)):
        if(i % 2 == 0):
            right.append(array[i])
        else:
            left.append(array[i])
        swaps += 1

    left, swaps, cmp = merge_sort(left, loggingEnabled, level + 1,
                                  swaps, cmp)

    right, swaps, cmp = merge_sort(right, loggingEnabled, level + 1,
                                   swaps, cmp)

    result, swaps, cmp = merge(left, right, loggingEnabled, level,
                               swaps, cmp)
    return result, swaps, cmp


def merge(left, right, loggingEnabled, level, swaps, cmp):
    result = []
    # disable logging for longer sublists
    if(loggingEnabled > 0):  # and len(left) < 32 and len(right) < 32):
        print('{0:2d} {1} {2:8} {3}'
              .format(level, '--'*(level), 'merging:', left[:32]), sep=' ')
        print('{0:2} {1} {2:>8} {3}'
              .format('', "--"*(level), '&', right[:32]), sep=' ')
    while(len(left) > 0 and len(right) > 0):
        cmp += 1
        if(left[0] <= right[0]):
            result.append(left[0])
            swaps += 1
            left = left[1:]
        else:
            result.append(right[0])
            swaps += 1
            right = right[1:]
        # swaps += 1
    # one of merged lists is empty now
    while(len(left) > 0):
        result.append(left[0])
        left = left[1:]
        swaps += 1

    while(len(right) > 0):
        result.append(right[0])
        right = right[1:]
        swaps += 1

    if(loggingEnabled > 0):  # and len(result) < 64):
        print('{0:2} {1} {2:>8} {3}'
              .format('', '--'*(level), '->', result[:64]), sep=' ')
    return result, swaps, cmp
