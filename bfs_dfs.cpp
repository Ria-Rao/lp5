#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <queue>
#include <stack>
using namespace std;

// Parallel BFS function
void parallel_bfs(int graph[6][6], int startnode, int numNodes) {
    bool visited[numNodes] = {false};
    visited[startnode] = true;
    queue<int> q;
    q.push(startnode);

    while (!q.empty()) {
        int level_size = q.size();
        #pragma omp parallel for
        for (int i = 0; i < level_size; i++) {
            int node;
            #pragma omp critical
            {
                node = q.front();
                q.pop();
                cout << "Visiting Node: " << node << " by thread " << omp_get_thread_num() << endl;
            }
            for (int neighbour = 0; neighbour < numNodes; neighbour++) {
                if (graph[node][neighbour] == 1 && !visited[neighbour]) {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }
}

// Parallel DFS function
void parallel_dfs(int graph[6][6], int startnode, int numNodes) {
    bool visited[numNodes] = {false};
    visited[startnode] = true;
    stack<int> s;
    s.push(startnode);

    while (!s.empty()) {
        int level_size = s.size();
        #pragma omp parallel for
        for (int i = 0; i < level_size; i++) {
            int node;
            #pragma omp critical
            {
                node = s.top();
                s.pop();
                cout << "Visiting Node " << node << " by thread " << omp_get_thread_num() << endl;
            }
            for (int neighbour = 0; neighbour < numNodes; neighbour++) {
                bool push_flag = false;
                if (graph[node][neighbour] == 1) {   // If there is a connection
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

int main() {
    int numNodes = 6;
    int graph[6][6] = {
        {0, 1, 1, 0, 0, 0},  // Node 0 is connected to nodes 1 and 2
        {1, 0, 0, 1, 1, 0},  // Node 1 is connected to nodes 0, 3, 4
        {1, 0, 0, 0, 1, 0},  // Node 2 is connected to nodes 0 and 4
        {0, 1, 0, 0, 0, 1},  // Node 3 is connected to nodes 1 and 5
        {0, 1, 1, 0, 0, 0},  // Node 4 is connected to nodes 1 and 2
        {0, 0, 0, 1, 0, 0}   // Node 5 is connected to node 3
    };

    // Call Parallel BFS
    cout << "Running Parallel BFS:" << endl;
    parallel_bfs(graph, 0, numNodes);

    cout << endl;

    // Call Parallel DFS
    cout << "Running Parallel DFS:" << endl;
    parallel_dfs(graph, 0, numNodes);

    return 0;
}

