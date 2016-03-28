import random


def quick_sort(array, loggingEnabled=0):
    return _quick_sort(array, loggingEnabled)


def _quick_sort(array, loggingEnabled=0,
                swaps=0, cmp=0):
    if len(array) <= 1:
        return array, swaps, cmp
    else:
        less = []
        more = []
        idx = random.randint(0, len(array)-1)
        pivot = array[idx]
        if loggingEnabled > 0:
            print("array: {0}".format(array[idx-10:idx+10]))
        for el in array:
            if loggingEnabled > 1:
                print("comparing: {} with pivot: {}".format(el, pivot))
            cmp += 1
            if el < pivot:
                less.append(el)
                swaps += 1
            else:
                cmp += 1
                if el > pivot:
                    more.append(el)
                    swaps += 1
        if loggingEnabled > 0:
            print("less: {}{}".format(less[:32], "..." if len(less) > 32
                                      else ''))
            print("pivot: {}".format(pivot))
            print("more: {}{}".format(more[:32], "..." if len(more) > 32
                                      else ''))
            print("-"*20)
        less, swaps, cmp = _quick_sort(less, loggingEnabled, swaps, cmp)
        more, swaps, cmp = _quick_sort(more, loggingEnabled, swaps, cmp)
        result = less + [pivot] * array.count(pivot) + more
        return result, swaps, cmp
