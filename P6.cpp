#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

// Define a graph node structure
struct Node {
    int id;
    vector<Node*> neighbors;
    bool visited;
};

// Function to perform BFS in parallel
void parallelBFS(Node* start) {
    
    #pragma omp parallel
    {
        queue<Node*> q;
        #pragma omp single
        {
            q.push(start);
            start->visited = true;
        }

        while (!q.empty()) {
            Node* current;
            #pragma omp critical
            {
                current = q.front();
                q.pop();
            }

            #pragma omp parallel for
            for (size_t i = 0; i < current->neighbors.size(); ++i) {
                Node* neighbor = current->neighbors[i];
                #pragma omp critical
                {
                    if (!neighbor->visited) {
                        neighbor->visited = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    // Create graph nodes
    vector<Node> graph(7);
    for (int i = 0; i < 7; ++i) {
        graph[i].id = i;
        graph[i].visited = false;
    }

    // Define graph connections
    graph[0].neighbors.push_back(&graph[1]);
    graph[0].neighbors.push_back(&graph[2]);
    graph[1].neighbors.push_back(&graph[3]);
    graph[1].neighbors.push_back(&graph[4]);
    graph[2].neighbors.push_back(&graph[5]);
    graph[2].neighbors.push_back(&graph[6]);

    // Perform BFS from the start node in parallel
    parallelBFS(&graph[0]);

    // Output visited nodes
    cout << "Visited nodes:" << endl;
    for (const auto& node : graph) {
        if (node.visited)
            cout << node.id << " ";
    }
    cout << endl;

    return 0;
}
