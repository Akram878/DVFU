#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// بنية لحفظ الجار والوزن
struct Edge {
    int to, weight;
};

// بنية لعنصر في الهيب
struct HeapNode {
    int vertex, dist;
};

// Min Heap يدوي
class MinHeap {
public:
    vector<HeapNode> heap;
    vector<int> pos;  // موقع كل رأس داخل الهيب

    MinHeap(int n) {
        heap.reserve(n + 1);
        pos.resize(n, -1);
    }

    void swap_nodes(int i, int j) {
        swap(heap[i], heap[j]);
        pos[heap[i].vertex] = i;
        pos[heap[j].vertex] = j;
    }

    void push(HeapNode node) {
        heap.push_back(node);
        int i = heap.size() - 1;
        pos[node.vertex] = i;
        sift_up(i);
    }

    void sift_up(int i) {
        while (i > 0 && heap[(i - 1) / 2].dist > heap[i].dist) {
            swap_nodes(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    void sift_down(int i) {
        int n = heap.size();
        while (true) {
            int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
            if (left < n && heap[left].dist < heap[smallest].dist) smallest = left;
            if (right < n && heap[right].dist < heap[smallest].dist) smallest = right;
            if (smallest == i) break;
            swap_nodes(i, smallest);
            i = smallest;
        }
    }

    HeapNode extract_min() {
        HeapNode min_node = heap[0];
        swap_nodes(0, heap.size() - 1);
        heap.pop_back();
        pos[min_node.vertex] = -1;
        if (!heap.empty()) sift_down(0);
        return min_node;
    }

    void decrease_key(int v, int new_dist) {
        int i = pos[v];
        if (i == -1) return;  // ليس موجودًا
        if (heap[i].dist > new_dist) {
            heap[i].dist = new_dist;
            sift_up(i);
        }
    }

    bool empty() {
        return heap.empty();
    }
};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int N, M, S;
    fin >> N >> M >> S;
    S--;

    vector<vector<Edge>> adj(N);

    for (int i = 0; i < M; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v, w});
    }

    vector<int> dist(N, INF);
    vector<bool> visited(N, false);
    dist[S] = 0;

    MinHeap heap(N);
    for (int i = 0; i < N; ++i)
        heap.push({i, dist[i]});

    while (!heap.empty()) {
        HeapNode node = heap.extract_min();
        int u = node.vertex;

        if (visited[u]) continue;
        visited[u] = true;

        for (Edge e : adj[u]) {
            int v = e.to;
            int w = e.weight;
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                heap.decrease_key(v, dist[v]);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        if (dist[i] == INF)
            fout << -1 << " ";
        else
            fout << dist[i] << " ";
    }

    fout << endl;
    return 0;
}
