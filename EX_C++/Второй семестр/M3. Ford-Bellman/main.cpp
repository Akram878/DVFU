#include <fstream>
#include <vector>
#include <tuple>
#include <limits>
using namespace std;

const int INF = 1e9;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int N, M, S;
    fin >> N >> M >> S;
    --S;

    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        edges.push_back(make_tuple(u - 1, v - 1, w));
    }

    vector<int> dist(N, INF);
    dist[S] = 0;

    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < edges.size(); ++j) {
            int u = get<0>(edges[j]);
            int v = get<1>(edges[j]);
            int w = get<2>(edges[j]);
            if (dist[u] < INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        if (dist[i] == INF)
            fout << " ";
        else
            fout << dist[i];
        if (i + 1 < N) fout << " ";
    }
    fout << "\n";

    return 0;
}
