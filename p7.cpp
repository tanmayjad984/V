#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>

using namespace std;

// Define a graph node structure
struct Node {
    int id;
    vector<Node*> neighbors;
    bool visited;
};

// Function to perform DFS in parallel
void parallelDFS(Node* start) {
    stack<Node*> s;
    start->visited = true;
    s.push(start);

    while (!s.empty()) {
        Node* current;
        #pragma omp critical
        {
            current = s.top();
            s.pop();
        }

        // Process current node
        cout << current->id << " ";

        // Explore neighbors
        #pragma omp parallel for
        for (size_t i = 0; i < current->neighbors.size(); ++i) {
            Node* neighbor = current->neighbors[i];
            #pragma omp critical
            {
                if (!neighbor->visited) {
                    neighbor->visited = true;
                    s.push(neighbor);
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

    // Perform DFS from the start node in parallel
    parallelDFS(&graph[0]);

    cout << endl;

    return 0;
}
