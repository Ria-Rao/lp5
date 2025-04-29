#include <iostream>
#include <omp.h>
using namespace std;

void merge(int *arr,int l,int m,int r){
	int n1=m-l+1;
	int n2=r-m;
	
	int leftarr[n1];
	int rightarr[n2];
	
	for(int i=0;i<n1;i++){
		leftarr[i]=arr[l+i];
	}
	
	for(int i=0;i<n2;i++){
		rightarr[i]=arr[m+1+i];
	}
	
	int i=0;
	int j=0;
	int k=l;
	while(i<n1 && j<n2){
		if(leftarr[i]>rightarr[j]){
			arr[k]=rightarr[j];
			j++;	
		}
		else{
			arr[k]=leftarr[i];
			i++;	
		}
		k++;
	}
	
	while (i < n1) {
        arr[k] = leftarr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightarr[j];
        j++;
        k++;
    }
	
}

void mergeSort(int *arr,int l,int r){
	if(l<r){
	   int m=(l+r)/2;
	   mergeSort(arr,l,m);
       mergeSort(arr,m+1,r);
       merge(arr,l,m,r);
	}
}

int main(){
	int arr[]={2,6,4,7,1};
	mergeSort(arr, 0, 4);
	cout << "Sorted array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
	return 0;	
}