#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

void bubblesort(int *arr,int n){
	min_val=arr[0];
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n-i-1;j++){
			if(arr[i]<min_val):
				temp=arr[i];
				arr[i]=min_val;
				min_val=arr[i];
		}
	}
}

int main(){
	int arr[]={2,7,8,9,3};
	int n=sizeof(arr)/sizeof(arr[0])
	bubblesort(arr,n)	
}