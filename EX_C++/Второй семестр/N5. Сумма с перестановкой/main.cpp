#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <set>




using namespace std;


ifstream fin("input.txt");
ofstream fout("output.txt");

vector<int> get_digit_counts(long long num) {
    vector<int> counts(10, 0);
    string s = to_string(num);
    for (char c : s) {
        counts[c - '0']++;
    }
    return counts;
}


set<long long> permutations_set;

int original_num_length;


void generate_permutations_recursive(string current_str, vector<int> current_digit_counts) {

    if (current_str.length() == original_num_length) {

        permutations_set.insert(stoll(current_str));
        return;
    }


    int start_digit = (current_str.empty() && original_num_length > 1) ? 1 : 0;

    for (int digit = start_digit; digit <= 9; ++digit) {
        if (current_digit_counts[digit] > 0) {
            current_digit_counts[digit]--;
            generate_permutations_recursive(current_str + to_string(digit), current_digit_counts);
            current_digit_counts[digit]++;
        }
    }
}

int main() {


    long long a, b, c;
    fin >> a >> b >> c;


    string s_a = to_string(a);
    original_num_length = s_a.length();

    vector<int> counts_a = get_digit_counts(a);

    permutations_set.clear();
    generate_permutations_recursive("", counts_a);

    vector<long long> perm_a(permutations_set.begin(), permutations_set.end());


    string s_b = to_string(b);
    original_num_length = s_b.length();

    vector<int> counts_b = get_digit_counts(b);

    permutations_set.clear();
    generate_permutations_recursive("", counts_b);

    set<long long> perm_b_set = permutations_set;


    for (long long x : perm_a) {
        long long y_target = c - x;


        if (y_target <= 0) {
            continue;
        }


        string s_y_target = to_string(y_target);
        if (s_y_target.length() == s_b.length()) {

            vector<int> counts_y_target = get_digit_counts(y_target);
            if (counts_y_target == counts_b) {

                fout << "YES\n";
                fout << x << " " << y_target << "\n";
                return 0;
            }
        }
    }


    fout << "NO\n";

    return 0;
}
