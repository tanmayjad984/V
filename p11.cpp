#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 1000

// Function to calculate the sum of elements in an array using parallel reduction
int parallelSum(int arr[], int n) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum;
}

// Function to calculate the average of elements in an array using parallel reduction
double parallelAverage(int arr[], int n) {
    int sum = parallelSum(arr, n);
    double average = (double)sum / n;
    return average;
}

int main() {
    // Initialize array with random values
    int arr[ARRAY_SIZE];
    srand(42);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    // Calculate the sum and average of elements in the array using parallel reduction
    int sum = parallelSum(arr, ARRAY_SIZE);
    double average = parallelAverage(arr, ARRAY_SIZE);

    printf("Sum of elements: %d\n", sum);
    printf("Average of elements: %.2f\n", average);

    return 0;
}
