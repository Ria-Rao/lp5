#include <iostream>
#include <omp.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortSequential(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortParallel(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, l, m);
            #pragma omp section
            mergeSortParallel(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 54, 43, 32, 21, 10, 9, 8, 7, 6, 5, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int arr_seq[n], arr_par[n];
    for (int i = 0; i < n; i++) {
        arr_seq[i] = arr_par[i] = arr[i];
    }

    // Sequential Merge Sort
    double start = omp_get_wtime();
    mergeSortSequential(arr_seq, 0, n-1);
    double seq_time = omp_get_wtime() - start;

    // Parallel Merge Sort
    start = omp_get_wtime();
    mergeSortParallel(arr_par, 0, n-1);
    double par_time = omp_get_wtime() - start;

    // Print final results only
    std::cout << "Sequential Merge Sort Result: ";
    for (int i = 0; i < n; i++) std::cout << arr_seq[i] << " ";
    std::cout << "\nTime: " << seq_time << " seconds\n\n";

    std::cout << "Parallel Merge Sort Result: ";
    for (int i = 0; i < n; i++) std::cout << arr_par[i] << " ";
    std::cout << "\nTime: " << par_time << " seconds\n";

    return 0;
}