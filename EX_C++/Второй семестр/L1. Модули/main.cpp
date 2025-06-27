#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);
        }
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;

    vector<vector<int>> graph(n + 1); // 1-based indexing
    vector<bool> visited(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int components = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, graph, visited);
            ++components;
        }
    }

    fout << components << endl;

    return 0;
}
