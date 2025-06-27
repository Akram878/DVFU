#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

const int straight_lines[10]  = {6, 2, 3, 2, 4, 5, 4, 2, 7, 4};
const int diagonal_lines[10]  = {0, 1, 1, 2, 0, 0, 1, 1, 0, 1};

struct State {
    int s, d;
    string value;
};


class MinHeap {
    vector<State> data;

    bool better(const string& a, const string& b) {
        if (a.length() != b.length()) return a.length() < b.length();
        return a < b;
    }

    bool cmp(const State& a, const State& b) {
        return better(a.value, b.value);
    }

    void siftUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (cmp(data[idx], data[parent])) {
                swap(data[idx], data[parent]);
                idx = parent;
            } else break;
        }
    }

    void siftDown(int idx) {
        int size = data.size();
        while (2 * idx + 1 < size) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = left;
            if (right < size && cmp(data[right], data[left]))
                smallest = right;
            if (cmp(data[smallest], data[idx])) {
                swap(data[smallest], data[idx]);
                idx = smallest;
            } else break;
        }
    }

public:
    void push(State s) {
        data.push_back(s);
        siftUp(data.size() - 1);
    }

    State top() {
        return data.front();
    }

    void pop() {
        swap(data.front(), data.back());
        data.pop_back();
        siftDown(0);
    }

    bool empty() {
        return data.empty();
    }
};

int main() {
    int max_straight, max_diag;
    cin >> max_straight >> max_diag;

    map<pair<int, int>, string> best;
    MinHeap q;

    q.push({0, 0, ""});
    best[{0, 0}] = "";

    while (!q.empty()) {
        State current = q.top(); q.pop();
        int s = current.s, d = current.d;
        string val = current.value;

        if (best[{s, d}] < val) continue;

        for (int digit = 0; digit < 10; ++digit) {
            int ns = s + straight_lines[digit];
            int nd = d + diagonal_lines[digit];

            if (ns > max_straight || nd > max_diag)
                continue;

            if (val.empty() && digit == 0)
                continue;

            string new_val = val + char('0' + digit);
            auto& existing = best[{ns, nd}];

            if (existing.empty() || new_val.length() < existing.length() ||
                (new_val.length() == existing.length() && new_val < existing)) {
                existing = new_val;
                q.push({ns, nd, new_val});
            }
        }
    }

    if (best.count({max_straight, max_diag}))
        cout << best[{max_straight, max_diag}];
    else
        cout << "Wrong";

    return 0;
}
