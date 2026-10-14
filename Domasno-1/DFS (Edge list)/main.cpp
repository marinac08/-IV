#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, int n, vector<pair<int, int>>& edges, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (auto edge : edges) {
        int neighbor = -1;

        if (edge.first == node)
            neighbor = edge.second;
        else if (edge.second == node)
            neighbor = edge.first;

        if (neighbor != -1 && !visited[neighbor])
            dfs(neighbor, n, edges, visited);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    int start;
    cin >> start;

    vector<bool> visited(n, false);

    dfs(start, n, edges, visited);

    return 0;
}
