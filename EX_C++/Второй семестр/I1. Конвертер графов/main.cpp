#include <fstream>
#include <vector>
#include <string>
using namespace std;

int N;
vector<vector<int>> adj;

void read_edges(ifstream &fin) {
    int M;
    fin >> N >> M;
    adj.assign(N, vector<int>());
    for (int i = 0; i < M; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }
}

void read_lists(ifstream &fin) {
    fin >> N;
    adj.assign(N, vector<int>());
    for (int i = 0; i < N; ++i) {
        int c;
        fin >> c;
        for (int j = 0; j < c; ++j) {
            int v;
            fin >> v;
            adj[i].push_back(v - 1);
        }
    }
}

void read_mat(ifstream &fin) {
    fin >> N;
    adj.assign(N, vector<int>());
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x;
            fin >> x;
            if (x == 1)
                adj[i].push_back(j);
        }
    }
}

void write_edges(ofstream &fout) {
    int M = 0;
    for (int i = 0; i < N; ++i)
        M += adj[i].size();
    fout << N << " " << M << "\n";
    for (int i = 0; i < N; ++i)
        for (int v : adj[i])
            fout << i + 1 << " " << v + 1 << "\n";
}

void write_lists(ofstream &fout) {
    fout << N << "\n";
    for (int i = 0; i < N; ++i) {
        fout << adj[i].size();
        for (int v : adj[i])
            fout << " " << v + 1;
        fout << "\n";
    }
}

void write_mat(ofstream &fout) {
    fout << N << "\n";
    for (int i = 0; i < N; ++i) {
        vector<int> row(N, 0);
        for (int v : adj[i])
            row[v] = 1;
        for (int j = 0; j < N; ++j) {
            fout << row[j];
            if (j < N - 1) fout << " ";
        }
        fout << "\n";
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    string in_format, out_format;
    fin >> in_format >> out_format;

    if (in_format == "edges") read_edges(fin);
    if (in_format == "lists") read_lists(fin);
    if (in_format == "mat") read_mat(fin);

    if (out_format == "edges") write_edges(fout);
    if (out_format == "lists") write_lists(fout);
    if (out_format == "mat") write_mat(fout);

    return 0;
}
