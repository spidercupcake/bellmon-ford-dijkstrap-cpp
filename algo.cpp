#include <iostream>
#include <vector>
#include <limits.h>
#include <stack>

using namespace std;

class Graph {
public:
    Graph(int V, int E) : V(V), E(E) {
        edges = new Edge[E];
    }

    ~Graph() {
        delete[] edges;
    }

    void addEdge(int index, int src, int dest, int weight) {
        edges[index].src = src;
        edges[index].dest = dest;
        edges[index].weight = weight;
    }

    void bellmanFord(int start) {
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1); // To store the shortest path tree
        dist[start] = 0;

        // Relax all edges V-1 times
        for (int i = 1; i <= V - 1; ++i) {
            for (int j = 0; j < E; ++j) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }

        // Check for negative-weight cycles
        for (int j = 0; j < E; ++j) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains negative weight cycle" << endl;
                return;
            }
        }

        // Print distances and paths
        cout << "Node\tDistance\tPath" << endl;
        for (int i = 0; i < V; ++i) {
            if (dist[i] == INT_MAX) {
                cout << i << "\tINF\t\tN/A" << endl;
            } else {
                cout << i << "\t" << dist[i] << "\t\t";
                printPath(i, parent);
                cout << endl;
            }
        }
    }

private:
    struct Edge {
        int src, dest, weight;
    };

    int V, E;
    Edge* edges;

    void printPath(int node, const vector<int>& parent) {
        stack<int> path;
        for (int v = node; v != -1; v = parent[v])
            path.push(v);
        
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
    }
};

int main() {
    int V, E;

    cout << "Enter the number of nodes: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V, E);

    cout << "Enter the edges in the format (src dest weight):" << endl;
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cout << "Edge " << i + 1 << ": ";
        cin >> src >> dest >> weight;
        g.addEdge(i, src, dest, weight);
    }

    int start;
    cout << "Enter the starting node: ";
    cin >> start;

    g.bellmanFord(start);

    return 0;
}
