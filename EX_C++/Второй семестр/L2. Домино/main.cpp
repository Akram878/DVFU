#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

struct Domino {
    int a, b;
    bool used = false;
    string toString() const {
        return to_string(a) + to_string(b);
    }
    Domino flip() const {
        return {b, a, used};
    }
};

bool dfs(int current, vector<Domino>& dominos, vector<bool>& used, vector<Domino>& result, int depth) {
    if (depth == dominos.size()) return true;
    for (int i = 0; i < dominos.size(); ++i) {
        if (used[i]) continue;
        if (dominos[i].a == current) {
            used[i] = true;
            result.push_back(dominos[i]);
            if (dfs(dominos[i].b, dominos, used, result, depth + 1)) return true;
            result.pop_back();
            used[i] = false;
        } else if (dominos[i].b == current) {
            used[i] = true;
            result.push_back(dominos[i].flip());
            if (dfs(dominos[i].a, dominos, used, result, depth + 1)) return true;
            result.pop_back();
            used[i] = false;
        }
    }
    return false;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    string s;
    in >> s;

    int N = s.length() / 2;
    vector<Domino> dominos;

    for (int i = 0; i < s.length(); i += 2) {
        dominos.push_back({s[i] - '0', s[i + 1] - '0'});
    }

    map<int, int> degree;
    for (int i = 0; i < dominos.size(); ++i) {
        degree[dominos[i].a]++;
        degree[dominos[i].b]++;
    }

    int odd = 0;
    for (map<int, int>::iterator it = degree.begin(); it != degree.end(); ++it) {
        int node = it->first;
        int deg = it->second;
        if (deg % 2 != 0) odd++;
    }

    if (odd != 0 && odd != 2) {
        out << "NO" << endl;
        return 0;
    }

    vector<Domino> result;
    vector<bool> used(dominos.size(), false);

    for (int i = 0; i < dominos.size(); ++i) {
        used[i] = true;
        result.push_back(dominos[i]);
        if (dfs(dominos[i].b, dominos, used, result, 1)) {
            for (int j = 0; j < result.size(); ++j) {
                out << result[j].toString();
                if (j != result.size() - 1) out << "-";
            }
            return 0;
        }
        result.pop_back();

        result.push_back(dominos[i].flip());
        if (dfs(dominos[i].a, dominos, used, result, 1)) {
            for (int j = 0; j < result.size(); ++j) {
                out << result[j].toString();
                if (j != result.size() - 1) out << "-";
            }
            return 0;
        }
        result.pop_back();
        used[i] = false;
    }

    out << "NO" << endl;
    return 0;
}
