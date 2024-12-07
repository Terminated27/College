#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INSERTION_SORT_THRESHOLD 10
#define ARR_SIZE 1024

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function with median-of-three pivot selection
int partition(int arr[], int low, int high) {
    // Median-of-three: Choose pivot as the median of arr[low], arr[high], arr[mid]
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) swap(&arr[mid], &arr[low]);
    if (arr[high] < arr[low]) swap(&arr[high], &arr[low]);
    if (arr[mid] < arr[high]) swap(&arr[mid], &arr[high]);
    int pivot = arr[high];

    // Partitioning process
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Insertion Sort for small subarrays
void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Optimized QuickSort function
void quickSort(int arr[], int low, int high) {
    while (low < high) {
        // Use Insertion Sort for small subarrays
        if (high - low < INSERTION_SORT_THRESHOLD) {
            insertionSort(arr, low, high);
            break;
        } else {
            // Partition the array
            int pi = partition(arr, low, high);

            // Tail recursion optimization
            if (pi - low < high - pi) {
                quickSort(arr, low, pi - 1);
                low = pi + 1;
            } else {
                quickSort(arr, pi + 1, high);
                high = pi - 1;
            }
        }
    }
}

// Utility function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[ARR_SIZE];

    // Seed the random number generator
    srand(time(NULL));

    // Fill the array with random integers less than 200
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand(); // Random integer in the range 0 - 2^31-1
    }

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
