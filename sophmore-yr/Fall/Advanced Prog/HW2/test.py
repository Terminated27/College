def mergeSort_3_way(alist):
    global test
    list_length = len(alist)
    if list_length <= 1:
        test = test + [alist]  # Base case: return a list containing the input list
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



# Example usage
alist_even = [10, 20, 30, 40, 50, 60, 70, 80, 90]  # Even-length list
alist_odd = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]  # Odd-length list
global test
test = []
result_even = mergeSort_3_way(alist_even)
result_odd = mergeSort_3_way(alist_odd)

print("Result for even-length list:", result_even)
print("Result for odd-length list:", result_odd)
print(test)