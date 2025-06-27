#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100001;

int N, M;
vector<vector<pair<int, int>>> adj(MAXN); // (neighbor, edge_id)
vector<bool> used_edge;
vector<int> degree;
vector<int> euler;

void find_eulerian_cycle(int start) {
    stack<int> stk;
    vector<int> path;
    stk.push(start);

    while (!stk.empty()) {
        int v = stk.top();
        while (!adj[v].empty() && used_edge[adj[v].back().second]) {
            adj[v].pop_back();
        }
        if (adj[v].empty()) {
            path.push_back(v);
            stk.pop();
        } else {
            auto [u, eid] = adj[v].back();
            adj[v].pop_back();
            used_edge[eid] = true;
            stk.push(u);
        }
    }

    if (path.size() != M + 1) {
        euler.clear();
        return;
    }

    reverse(path.begin(), path.end());
    euler = path;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> N >> M;
    degree.resize(N + 1, 0);
    used_edge.resize(M, false);

    int u, v;
    for (int i = 0; i < M; ++i) {
        fin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        degree[u]++;
        degree[v]++;
    }

    for (int i = 1; i <= N; ++i) {
        if (degree[i] % 2 != 0) {
            fout << -1 << endl;
            return 0;
        }
    }

    // ابدأ من أي رأس لديه درجة > 0
    int start = 1;
    while (start <= N && adj[start].empty()) start++;

    find_eulerian_cycle(start);

    if (euler.empty()) {
        fout << -1 << endl;
    } else {
        for (int v : euler) {
            fout << v << " ";
        }
        fout << endl;
    }

    return 0;
}
