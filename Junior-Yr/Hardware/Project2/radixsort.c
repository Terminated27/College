#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 4096

// Utility function to find the maximum value in the array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Counting sort for a specific digit (exp is the current digit's place value)
void countingSort(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int)); // Output array
    int count[10] = {0};

    // Count occurrences of each digit in the current place
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Update count[i] to represent positions in output array
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array back to arr
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

// Main Radix Sort function
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);

    // Perform counting sort for each digit (1's, 10's, 100's, ...)
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

// Utility function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {

int arr[ARR_SIZE];

    // Seed the random number generator
    srand(time(NULL));

    // Fill the array with random integers less than 200
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand(); // Random integer in the range [0, 2^31-1]
    }
    
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    radixSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
