#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

pair<int, int> arr[200005];
int n, k;

// ------------------------
// Heap functions
// ------------------------

vector<int> minHeap;

void heapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (minHeap[parent] <= minHeap[idx]) break;
        swap(minHeap[parent], minHeap[idx]);
        idx = parent;
    }
}

void heapifyDown(int idx) {
    int size = minHeap.size();
    while (2 * idx + 1 < size) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = left;

        if (right < size && minHeap[right] < minHeap[left]) {
            smallest = right;
        }

        if (minHeap[idx] <= minHeap[smallest]) break;

        swap(minHeap[idx], minHeap[smallest]);
        idx = smallest;
    }
}

void insert(int val) {
    minHeap.push_back(val);
    heapifyUp(minHeap.size() - 1);
}

void popMin() {
    if (minHeap.empty()) return;
    minHeap[0] = minHeap.back();
    minHeap.pop_back();
    heapifyDown(0);
}

int getMin() {
    return minHeap[0];
}

// ------------------------
// Sorting: quickSort
// ------------------------

void quickSort(int left, int right) {
    if (left >= right) return;
    int pivot = arr[(left + right) / 2].first;
    int i = left, j = right;
    while (i <= j) {
        while (arr[i].first > pivot) i++;
        while (arr[j].first < pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quickSort(left, j);
    quickSort(i, right);
}

// ------------------------
// Main
// ------------------------

int main() {
    ifstream fin("power.in");
    ofstream fout("power.out");

    fin >> n >> k;

    for (int i = 0; i < n; i++) {
        fin >> arr[i].first >> arr[i].second;
    }

    quickSort(0, n - 1);

    long long max_area = 0;

    for (int i = 0; i < n; i++) {
        int x = arr[i].first;
        int y = arr[i].second;

        insert(y);
        if ((int)minHeap.size() > k) {
            popMin();
        }

        if ((int)minHeap.size() == k) {
            long long min_y = getMin();
            long long area = 1LL * x * min_y;
            if (area > max_area)
                max_area = area;
        }
    }

    fout << max_area << "\n";
    return 0;
}
