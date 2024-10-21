
def merge2List(alist, lefthalf, righthalf, i, j, pos):

    comparison = 0
    while i < len(lefthalf) and j < len(righthalf):
        if lefthalf[i] < righthalf[j]:
            alist[pos] = righthalf[j]
            j += 1
        else:
            alist[pos] = lefthalf[i]
            i += 1
        comparison += 1
        pos += 1

    while i < len(lefthalf):
        alist[pos] = lefthalf[i]
        i = i + 1
        pos += 1

    while j < len(righthalf):
        alist[pos]=righthalf[j]
        j=j+1
        pos += 1
    return comparison

def mergeSort_3_way(alist):
    list_length = len(alist)
    if list_length <= 1:
        arr + alist  # Base case: return a list containing the input list
    if list_length % 3 == 0:
        factor = True
    else:
        factor = False
    if factor == True:
        third = list_length // 3
        first_third = mergeSort_3_way(alist[:third])
        second_third = mergeSort_3_way(alist[third:2 * third])
        third_third = mergeSort_3_way(alist[2 * third:])

        return first_third + second_third + third_third
    else:
        front_part = mergeSort_3_way(alist[:-1])  # Slice to get all elements except the last one
        last_value = [alist[-1]]  # Create a list with the last element

        return front_part + last_value


arr = [5, 10, 9, 6, 8, 3, 1, 4, 2, 7]
mergeSort_3_way(arr)
print(arr)
