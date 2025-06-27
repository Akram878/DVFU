#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int E, F, N;
    fin >> E >> F >> N;
    int W = F - E;

    vector<int> dp(W + 1, INF);
    dp[0] = 0;

    vector<int> val(N), wt(N);
    for (int i = 0; i < N; ++i) {
        fin >> val[i] >> wt[i];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = wt[i]; j <= W; ++j) {
            if (dp[j - wt[i]] != INF) {
                dp[j] = min(dp[j], dp[j - wt[i]] + val[i]);
            }
        }
    }

    if (dp[W] == INF)
        fout << -1 << endl;
    else
        fout << dp[W] << endl;

    return 0;
}
