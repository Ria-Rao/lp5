#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;

int parallel_min(int *arr,int n){
	int min_val=arr[0];
	#pragma omp parallel for reduction(min:min_val)
	for(int i=0;i<n;i++){
		if (arr[i]<min_val){
			min_val=arr[i];
		}
	}
	return min_val;
}

int parallel_max(int *arr,int n){
	int max_val=arr[0];
	#pragma omp parallel for reduction(max:max_val)
	for(int i=0;i<n;i++){
		if (arr[i]>max_val){
			max_val=arr[i];
		}
	}
	return max_val;
}

double parallel_avg(int *arr,int n){
	int sum=0;
	#pragma omp parallel for reduction(+:sum)
	for(int i=0;i<n;i++){
		sum+=arr[i];	
	}
	double avg=sum/n;
	return avg;
}

int main(){
	int arr[]={10,20,30,40,50,60,70,80,90,100};
	int n=sizeof(arr)/sizeof(arr[0]);
	int min=parallel_min(arr,n);
	int max=parallel_max(arr,n);
	double avg=parallel_avg(arr,n);
	cout<<"Min :"<<min<<endl;
	cout<<"Max :"<<max<<endl;
	cout<<"Avg :"<<avg<<endl;
}