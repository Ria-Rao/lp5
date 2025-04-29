#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <stack>
using namespace std;

void parallel_dfs(int graph[6][6],int startnode,int numNodes){
	bool visited[numNodes]={false};
	visited[startnode]=true;
	stack <int> s;
	s.push(startnode);
	while(!s.empty()){
		int level_size=s.size();
		#pragma omp parallel for
		for(int i=0;i<level_size;i++){
			int node;
			#pragma omp critical 
			{
				node=s.top();
				s.pop();
				cout<<"Visiting Node"<<node<<"by thread"<<omp_get_thread_num()<<endl;
			}
			for(int neighbour=0;neighbour<numNodes;neighbour++){
				bool push_flag=false;
				if (graph[node][neighbour] == 1) {   // If there is a connection
                bool push_flag = false;

                #pragma omp critical
                {
                    if (!visited[neighbour]) {   // If neighbor is not visited
                        visited[neighbour] = true;
                        push_flag = true;
                    }
                }

                if (push_flag) {
                    #pragma omp critical
                    {
                        s.push(neighbour);       // Push unvisited neighbor
                    }
                }
			}
		}
	}
}
}
int main(){
	int numNodes=6;
	int graph[6][6]={
		{0, 1, 1, 0, 0, 0}, 
        {1, 0, 0, 1, 1, 0}, 
        {1, 0, 0, 0, 1, 0}, 
        {0, 1, 0, 0, 0, 1}, 
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0}
	};
	parallel_dfs(graph,0,numNodes);
	return 0;
}


