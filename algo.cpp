#include <iostream>

using namespace std;

class Graph {
public:
    Graph(int V, int E, int linkList[][3]) : V(V), E(E) {
        matrix = new int*[V];
        for (int i = 0; i < V; ++i) {
            matrix[i] = new int[V];
            for (int j = 0; j < V; ++j) {
                matrix[i][j] = INF; // Initialize with INF
            }
        }

        // Populate matrix from the link list
        for (int i = 0; i < E; ++i) {
            int src = linkList[i][0];
            int dest = linkList[i][1];
            int weight = linkList[i][2];
            matrix[src][dest] = weight;
        }
    }

    ~Graph() {
        for (int i = 0; i < V; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void bellmanFord(int start) {
        int* dist = new int[V];
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
        }
        dist[start] = 0;

        // Relax all links repeatedly
        for (int i = 1; i <= V - 1; ++i) {
            for (int u = 0; u < V; ++u) {
                for (int v = 0; v < V; ++v) {
                    if (matrix[u][v] != INF && dist[u] != INF && dist[u] + matrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + matrix[u][v];
                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (matrix[u][v] != INF && dist[u] != INF && dist[u] + matrix[u][v] < dist[v]) {
                    cout << "Graph contains negative weight cycle" << endl;
                    delete[] dist;
                    return;
                }
            }
        }

        // Print distances
        cout << "Vertex Distance from Source" << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << "\t\t" << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
        }

        delete[] dist;
    }

private:
    int V, E;
    int** matrix;
    static const int INF = 1e9; // Large number representing infinity
};

int main() {
    int V = 4; // Number of vertices
    int E = 4; // Number of links

    // Define a 2D array for links (source, destination, weight)
    int linkList[4][3] = {
        {0, 1, 2},
        {0, 3, 4},
        {1, 2, 3},
        {2, 3, 1}
    };

    Graph g(V, E, linkList);

    int start = 0; // Starting vertex
    g.bellmanFord(start);

    return 0;
}
