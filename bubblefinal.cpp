#include <iostream>
#include <omp.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void bubbleSortSequential(int arr[], int n) {
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void bubbleSortParallel(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int phase = i % 2;

        #pragma omp parallel for
        for (int j = phase; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 54, 43, 32, 21, 10, 9, 8, 7, 6, 5, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int arr_parallel[n];
    for (int i = 0; i < n; i++) {
        arr_parallel[i] = arr[i];
    }

    std::cout << "Original array: ";
    printArray(arr, n);

    // Sequential Bubble Sort
    double start = omp_get_wtime();
    bubbleSortSequential(arr, n);
    double end = omp_get_wtime();
    std::cout << "\nSequential Bubble Sort: ";
    printArray(arr, n);
    std::cout << "Time: " << (end - start) << " seconds\n";

    // Parallel Bubble Sort
    start = omp_get_wtime();
    bubbleSortParallel(arr_parallel, n);
    end = omp_get_wtime();
    std::cout << "\nParallel Bubble Sort: ";
    printArray(arr_parallel, n);
    std::cout << "Time: " << (end - start) << " seconds\n";

    return 0;
}