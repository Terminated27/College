def reverseList(A, i, j):
    if i >= j:
        return 
    A[i], A[j] = A[j], A[i]
    reverseList(A, i + 1, j - 1)
    
def test_reverseList():
    # Test case 1: Reverse a list with even number of elements
    A = [1, 2, 3, 4, 5, 6]
    reverseList(A, 0, len(A) - 1)
    assert A == [6, 5, 4, 3, 2, 1], "Test case 1 failed"
    
    # Test case 2: Reverse a list with odd number of elements
    B = [9, 8, 7, 6, 5]
    reverseList(B, 0, len(B) - 1)
    assert B == [5, 6, 7, 8, 9], "Test case 2 failed"
    
    # Test case 3: Reverse an empty list
    C = []
    reverseList(C, 0, len(C) - 1)
    assert C == [], "Test case 3 failed"
    
    # Test case 4: Reverse a list with only one element
    D = [42]
    reverseList(D, 0, len(D) - 1)
    assert D == [42], "Test case 4 failed"
    
    # Test case 5: Reverse a list with duplicate elements
    E = [3, 3, 3, 3]
    reverseList(E, 0, len(E) - 1)
    assert E == [3, 3, 3, 3], "Test case 5 failed"
    
    print("All test cases passed successfully!")

# Run the test cases
test_reverseList()
