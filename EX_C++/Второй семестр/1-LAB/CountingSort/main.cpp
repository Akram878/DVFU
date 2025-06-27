#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
using namespace chrono;

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);

    for (int num : arr) {
        count[num]++;
    }

    int index = 0;
    for (int i = 0; i <= maxVal; ++i) {
        while (count[i]-- > 0) {
            arr[index++] = i;
        }
    }
}

int main() {
    srand(time(0));

    vector<int> sizes = {10, 100, 1000, 10000};
    ofstream file("counting_sort_results.csv");

    file << "N";
    for (int i = 1; i <= 10; ++i)
        file << ",T" << i;
    file << ",Total(ms),Average(ms)" << endl;

    for (int N : sizes) {
        file << N;
        double totalTime = 0;


        int repetitions = (N <= 10000) ? 1000 : 1;

        for (int trial = 0; trial < 10; ++trial) {

            vector<int> original(N);
            for (int i = 0; i < N; ++i)
                original[i] = rand() % 10000;

            auto start = high_resolution_clock::now();

            for (int r = 0; r < repetitions; ++r) {
                vector<int> arr = original;
                countingSort(arr);
            }

            auto end = high_resolution_clock::now();
            double duration = duration_cast<microseconds>(end - start).count() / (1000.0 * repetitions);
            totalTime += duration;
            file << "," << fixed << setprecision(3) << duration;
        }

        file << "," << fixed << setprecision(3) << totalTime
             << "," << fixed << setprecision(3) << (totalTime / 10.0) << endl;
    }

    file.close();
    cout << "Result has saved in : counting_sort_results.csv" << endl;
    return 0;
}
