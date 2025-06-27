#include <fstream>
#include <vector>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

void custom_sort(vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

string solve(int n, int m, long long k, vector<int>& exits) {
    custom_sort(exits);

    vector<long long> rightFlow(m - 1, 0);
    long long curLoad = exits[0];
    if (curLoad > k) return "NO";

    for (int i = 0; i + 1 < m; ++i) {
        long long dist = exits[i + 1] - exits[i] - 1;
        long long futureLoad = curLoad + dist;
        long long extra = futureLoad > k ? futureLoad - k : 0;

        if (extra > dist) return "NO";
        rightFlow[i] = extra;
        curLoad = extra;
    }

    curLoad = n - 1 - exits[m - 1];
    if (curLoad > k) return "NO";
    vector<long long> leftFlow(m - 1, 0);

    for (int i = m - 1; i > 0; --i) {
        long long dist = exits[i] - exits[i - 1] - 1;
        long long futureLoad = curLoad + dist;
        long long extra = futureLoad > k ? futureLoad - k : 0;

        if (extra > dist) return "NO";
        leftFlow[i - 1] = extra;
        curLoad = extra;
    }

    if (curLoad + exits[0] > k) return "NO";

    string result(n, ' ');
    for (int idx : exits) result[idx] = 'X';

    for (int i = 0; i < exits[0]; ++i) result[i] = 'R';
    for (int i = exits[m - 1] + 1; i < n; ++i) result[i] = 'L';

    for (int i = 0; i < m - 1; ++i) {
        int start = exits[i] + 1;
        int end = exits[i + 1];
        int total = end - start;
        long long leftPeople = leftFlow[i];
        long long rightPeople = total - leftPeople;

        if (leftPeople + rightPeople > total) return "NO";

        for (int j = 0; j < leftPeople; ++j) result[start + j] = 'L';
        for (int j = leftPeople; j < total; ++j) result[start + j] = 'R';
    }

    return result;
}

int main() {
    int N, M;
    long long K;
    fin >> N >> M >> K;

    vector<int> exits(M);
    for (int i = 0; i < M; ++i) {
        fin >> exits[i];
        exits[i]--;
    }

    string answer = solve(N, M, K, exits);
    fout << answer << '\n';
    return 0;
}
