#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int N, M, S;
    fin >> N >> M >> S;
    S--; // تحويل الفهرسة إلى صفرية

    vector<vector<pair<int, int>>> graph(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        u--; v--; // تحويل الفهرسة إلى صفرية
        graph[u].push_back({v, w});
    }

    vector<int> dist(N, INF);
    vector<bool> used(N, false);
    dist[S] = 0;

    for (int i = 0; i < N; i++) {
        int u = -1;
        // البحث عن الرأس ذو المسافة الأصغر الذي لم يُستخدم بعد
        for (int j = 0; j < N; j++) {
            if (!used[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF)
            break; // باقي الرؤوس غير قابلة للوصول

        used[u] = true;

        // تحديث المسافات للجيران
        for (auto edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // إخراج النتائج
    for (int i = 0; i < N; i++) {
        if (dist[i] == INF)
            fout << -1 << " ";
        else
            fout << dist[i] << " ";
    }

    return 0;
}
