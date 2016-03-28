def insert_sort(array, loggingEnabled):
    """insertion sort implementation with logging & operation counting"""
    swaps = 0
    cmp = 0
    for i in range(1, len(array)):
        key = array[i]
        if(loggingEnabled > 0):
            print("key: {}".format(key))
        j = i - 1
        cmp += 1
        if(loggingEnabled > 0):
            print_key("\tbefore: ", array, i)
        while j >= 0 and array[j] > key:
            cmp += 1
            # print("[{}]".format(array[j]))
            array[j+1] = array[j]
            swaps += 1
            j = j - 1
        array[j+1] = key
        if(loggingEnabled > 0):
            print_key("\tafter: ", array, j+1)
        swaps += 1
    return array, swaps, cmp


def print_key(string, array, key_idx):
    print(string + "[", end='')
    for i in range(0, len(array)):
        if i == key_idx:
            if i == len(array) - 1:
                print("*{}*".format(array[i]), end='')
            else:
                print("*{}*, ".format(array[i]), end='')
        else:
            if i == len(array) - 1:
                print("{}".format(array[i]), end='')
            else:
                print("{}, ".format(array[i]), end='')
    print("]")
