#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;

// Parallel versions
int parallel_min(int *arr, int n) {
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for(int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

int parallel_max(int *arr, int n) {
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for(int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

double parallel_avg(int *arr, int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++) {
        sum += arr[i];    
    }
    return (double)sum / n;
}

// Sequential versions
int sequential_min(int *arr, int n) {
    int min_val = arr[0];
    for(int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

int sequential_max(int *arr, int n) {
    int max_val = arr[0];
    for(int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

double sequential_avg(int *arr, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += arr[i];    
    }
    return (double)sum / n;
}

int main() {
    int arr[] = {10,20,30,40,50,60,70,80,90,100};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    // Time measurements
    double start, end;
    
    // Sequential operations
    start = omp_get_wtime();
    int seq_min = sequential_min(arr, n);
    int seq_max = sequential_max(arr, n);
    double seq_avg = sequential_avg(arr, n);
    end = omp_get_wtime();
    double seq_time = end - start;
    
    // Parallel operations
    start = omp_get_wtime();
    int par_min = parallel_min(arr, n);
    int par_max = parallel_max(arr, n);
    double par_avg = parallel_avg(arr, n);
    end = omp_get_wtime();
    double par_time = end - start;
    
    // Output results
    cout << "Sequential Results:\n";
    cout << "Min: " << seq_min << endl;
    cout << "Max: " << seq_max << endl;
    cout << "Avg: " << seq_avg << endl;
    cout << "Time: " << seq_time << " seconds\n\n";
    
    cout << "Parallel Results:\n";
    cout << "Min: " << par_min << endl;
    cout << "Max: " << par_max << endl;
    cout << "Avg: " << par_avg << endl;
    cout << "Time: " << par_time << " seconds\n";
    
    return 0;
}
