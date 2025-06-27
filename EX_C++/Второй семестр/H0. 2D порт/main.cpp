#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }


    vector<long long> dp(n + 2, 0);


    for (int i = n - 1; i >= 0; --i) {

        long long option1 = dp[i + 1];

        long long option2 = 0;

        if (i + 1 < n) {

            long long current_containers = min(c[i], c[i+1]);

            option2 = current_containers + dp[i + 2];
        }


        dp[i] = max(option1, option2);
    }


    cout << dp[0] << endl;

    return 0;
}
