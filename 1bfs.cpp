#include<bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int numVertices;          
    vector<vector<int>> adj;

    public:
        Graph(int vertices) : numVertices(vertices), adj(vertices){}

        void addEdge(int src, int dest){
            adj[src].push_back(dest);
            adj[dest].push_back(src);
        }

        void viewGraph() {
            cout << "Graph:\n";
            for (int i = 0; i < numVertices; i++) {
                cout << "Vertex " << i << " -> ";
                for (int neighbor : adj[i]) {
                    cout << neighbor << " ";
                }
                cout << endl;
            }
        }

        void bfs(int startVertex){
            vector<int> visited(numVertices, false);
            visited[startVertex] = true;

            queue<int> q;
            q.push(startVertex);

            while(!q.empty()){
                int curr = q.front();
                q.pop();
                cout<<curr<<" ";

                #pragma omp for parallel
                for(int neighbour : adj[curr]){
                    if(!visited[neighbour]){
                        visited[neighbour] = true;
                        q.push(neighbour);
                    }
                }
            }
        }

};


int main(){
    int numVertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    Graph graph(numVertices);

    int numEdges;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges (source destination):\n";
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    graph.viewGraph();

    int startVertex;
    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> startVertex;

    cout << "Breadth First Search (BFS): ";
    graph.bfs(startVertex);
    cout << endl;

    return 0;

}