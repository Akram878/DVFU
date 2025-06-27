#include <vector>
#include <fstream>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    vector<vector<long long>> cost(n, vector<long long>(n));
    for (int from = 0; from < n; ++from) {
        for (int to = 0; to < n; ++to) {
            fin >> cost[from][to];
            if (cost[from][to] == -1) cost[from][to] = INF;
        }
    }

    // dp[state][current]: minimal cost to reach "current" with visited state
    vector<vector<long long>> dp(1 << n, vector<long long>(n, INF));

    // Initialize starting positions (starting from any planet)
    for (int start = 0; start < n; ++start) {
        dp[1 << start][start] = 0;
    }

    for (int state = 0; state < (1 << n); ++state) {
        for (int u = 0; u < n; ++u) {
            if (!(state & (1 << u)) || dp[state][u] == INF) continue;

            for (int v = 0; v < n; ++v) {
                if (state & (1 << v)) continue; // already visited
                if (cost[u][v] == INF) continue; // no direct path

                int nextState = state | (1 << v);
                long long newCost = dp[state][u] + cost[u][v];

                if (newCost < dp[nextState][v]) {
                    dp[nextState][v] = newCost;
                }
            }
        }
    }

    long long result = INF;
    int allVisited = (1 << n) - 1;
    for (int last = 0; last < n; ++last) {
        result = min(result, dp[allVisited][last]);
    }

    fout << (result == INF ? -1 : result) << '\n';

    return 0;
}
