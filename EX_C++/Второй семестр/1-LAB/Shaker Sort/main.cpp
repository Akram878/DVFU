#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;
using namespace chrono;


void shakerSort(int arr[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}


void fillArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

int main() {
    srand(time(0));
    ofstream fout("shaker_sort_results.csv");


    fout << "N,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,Total(ms),Average(ms)\n";

    vector<int> Ns = {10 , 100 , 1000, 10000};//sorry but this my device ability

    for (int n : Ns) {
        fout << n;
        double total = 0;


        int repeatCount;
        if (n == 10 || n == 100)
            repeatCount = 10000;
        else if (n == 1000 )
            repeatCount = 1000;
        else
            repeatCount = 1;

        for (int t = 0; t < 10; t++) {
            double trialTimeMicro = 0;

            for (int r = 0; r < repeatCount; r++) {
                int* arr = new int[n];
                fillArray(arr, n);

                auto start = high_resolution_clock::now();
                shakerSort(arr, n);
                auto end = high_resolution_clock::now();

                trialTimeMicro += duration_cast<microseconds>(end - start).count();

                delete[] arr;
            }


            double trialTime = trialTimeMicro / repeatCount / 1000.0;
            total += trialTime;

            fout << "," << fixed << setprecision(6) << trialTime;
        }

        double avg = total / 10.0;
        fout << "," << fixed << setprecision(6) << total << "," << avg << "\n";
    }

    fout.close();
    cout << "Result has been saved in: shaker_sort_results.csv" << endl;
    return 0;
}
