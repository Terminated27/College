def factorial(n):
    #assumed positive input
    if n == 0:
        return 1
    return n * factorial(n-1)
def test_factorial():
    # Test case 1: Factorial of 0 should be 1
    assert factorial(0) == 1, "Test case 1 failed"
    
    # Test case 2: Factorial of 1 should be 1
    assert factorial(1) == 1, "Test case 2 failed"
    
    # Test case 3: Factorial of a positive number
    assert factorial(5) == 120, "Test case 3 failed"  # 5! = 5 * 4 * 3 * 2 * 1 = 120
    
    # Test case 4: Factorial of a large positive number
    assert factorial(10) == 3628800, "Test case 4 failed"  # 10! = 3628800
    
    print("All test cases passed successfully!")

# Run the test cases
test_factorial()