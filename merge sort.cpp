#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int temp[10], i = l, j = m+1, k = l;
    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = temp[i];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    int arr[5] = {5, 2, 4, 1, 3};
    mergeSort(arr, 0, 4);
    cout << "Sorted Array: ";
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
}