#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 1000

// Function to find the minimum value in an array using parallel reduction
int parallelMin(int arr[], int n) {
    int min_val = arr[0];

    #pragma omp parallel for reduction(min:min_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    return min_val;
}

// Function to find the maximum value in an array using parallel reduction
int parallelMax(int arr[], int n) {
    int max_val = arr[0];

    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    return max_val;
}

int main() {
    // Initialize array with random values
    int arr[ARRAY_SIZE];
    srand(42);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    // Find the minimum and maximum values in the array using parallel reduction
    int min_val = parallelMin(arr, ARRAY_SIZE);
    int max_val = parallelMax(arr, ARRAY_SIZE);

    printf("Minimum value: %d\n", min_val);
    printf("Maximum value: %d\n", max_val);

    return 0;
}
