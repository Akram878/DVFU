#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;

const int MOD = 1000000000;


int N_max;
int L_max;
int POS_OFFSET;



vector<vector<vector<int>>> recursive_dp;


long long calculate_recursive_dp(int j, int p_offset, int s) {

    if (j > N_max || s > L_max) {
        return 0;
    }

    if (p_offset < 0 || p_offset > 2 * L_max) {
        return 0;
    }


    if (recursive_dp[j][p_offset][s] != -1) {
        return recursive_dp[j][p_offset][s];
    }


    if (j == 0 && p_offset == POS_OFFSET && s == 0) {
        return recursive_dp[j][p_offset][s] = 1;
    }

    if (j == 0) {
        return recursive_dp[j][p_offset][s] = 0;
    }


    long long current_ways = 0;
    int current_p_from_offset = p_offset - POS_OFFSET;

    for (int abs_last_jump = 1; abs_last_jump <= L_max; ++abs_last_jump) {
        int prev_s = s - abs_last_jump;

        if (prev_s < 0) {
            break;
        }


        int prev_p_plus = current_p_from_offset - abs_last_jump;

        if (abs(prev_p_plus) <= L_max) {
             current_ways = (current_ways + calculate_recursive_dp(j - 1, prev_p_plus + POS_OFFSET, prev_s)) % MOD;
        }


        int prev_p_minus = current_p_from_offset + abs_last_jump;
        if (abs(prev_p_minus) <= L_max) {
             current_ways = (current_ways + calculate_recursive_dp(j - 1, prev_p_minus + POS_OFFSET, prev_s)) % MOD;
        }
    }


    return recursive_dp[j][p_offset][s] = current_ways;
}

int main() {


    int A_input, B_input;
    cin >> A_input >> B_input >> N_max >> L_max;

    int target_displacement = B_input - A_input;


    POS_OFFSET = L_max;


    recursive_dp.assign(N_max + 1,
                        vector<std::vector<int>>(2 * L_max + 1,
                                                      vector<int>(L_max + 1, -1))); // -1 indicates not computed


    if (abs(target_displacement) > L_max) {
        cout << 0 << endl;
        return 0;
    }

    long long total_result = 0;


    for (int j = 1; j <= N_max; ++j) {

        for (int s = abs(target_displacement); s <= L_max; ++s) {

            int target_p_offset = target_displacement + POS_OFFSET;

            total_result = (total_result + calculate_recursive_dp(j, target_p_offset, s)) % MOD;
        }
    }


    if (target_displacement == 0) {
        total_result = (total_result + 1) % MOD;
    }

    cout << total_result << endl;

    return 0;
}
