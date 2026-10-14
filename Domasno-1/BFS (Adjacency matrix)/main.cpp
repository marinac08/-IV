#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> bfsTraversal(int v, 
            vector<vector<int>> &edges, int src) {

    vector<vector<int>> adj(v, vector<int>(v, 0));

    for (auto &edge : edges) {
        int a = edge[0];
        int b = edge[1];
        adj[a][b] = 1;
        adj[b][a] = 1;  
    }

    vector<bool> visited(v, false);
    vector<int> res;
    queue<int> q;

    visited[src] = true;
    q.push(src);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        res.push_back(curr);

        for (int i = 0; i < v; i++) {
            if (adj[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    return res;
}

int main() {
    int v = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}};
    int src = 0;

    vector<int> traversal = bfsTraversal(v, edges, src);
    
    for (int x : traversal) {
        cout << x << " ";
    }

    return 0;
}
