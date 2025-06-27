#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;


void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];


    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);


        merge(arr, left, mid, right);
    }
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    int n, k;
    inputFile >> n >> k;

    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        inputFile >> numbers[i];
    }


    vector<int> largestK;
    for (int i = 0; i < n; ++i) {
        if (largestK.size() < k) {
            largestK.push_back(numbers[i]);
        } else {
            int minVal = largestK[0];
            int minIndex = 0;
            for (int j = 1; j < k; ++j) {
                if (largestK[j] < minVal) {
                    minVal = largestK[j];
                    minIndex = j;
                }
            }
            if (numbers[i] > minVal) {
                largestK[minIndex] = numbers[i];
            }
        }
    }


    mergeSort(largestK, 0, largestK.size() - 1);


    for (int num : largestK) {
        outputFile << num << " ";
    }
    outputFile << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
