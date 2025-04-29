#include <iostream>
#include <omp.h>
#include <cmath>
using namespace std;

float distance(float x1,float y1,float x2,float y2){
	return sqrt(((x1-x2)*(x1-x2))-((y1-y2)*(y1-y2)));
}

int main(){
	float points[4][2] = {
        {1.0, 2.0},  // Point 0
        {2.0, 3.0},  // Point 1
        {8.0, 8.0},  // Point 2
        {9.0, 9.0}   // Point 3
    };

    // Define the centroids (Here, I assume you have two centroids)
    float centroids[2][2] = {
        {1.5, 2.5},  // Centroid 0
        {8.5, 8.5}   // Centroid 1
    };

	int cluster[4];
	#pragma omp parallel for
	for(int i=0;i<4;i++){
		float d0=distance(points[i][0],points[i][1],centroids[0][0],centroids[0][1]);
		float d1=distance(points[i][0],points[i][1],centroids[1][0],centroids[1][1]);
		if(d0<d1){
			cluster[i]=0;
		}
		else{
			cluster[i]=1;
		}		
	}
	    for (int i = 0; i < 4; i++) {
        cout << "Point (" << points[i][0] << ", " << points[i][1] << ") -> Cluster " << cluster[i] << endl;
    }

}