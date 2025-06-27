#include <iostream>
#include <fstream>
using namespace std;


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int B, G, TB, TG;
    in >> B >> G >> TB >> TG;

    int total = B + G;


    int times[100];
    int idx = 0;


    for (int i = 0; i < B; i++) times[idx++] = TB;


    for (int i = 0; i < G; i++) times[idx++] = TG;


    bubbleSort(times, total);

    int time = 0;
    int i = total - 1;

    while (i >= 3) {


        int option1 = 2 * times[1] + times[0] + times[i];

        int option2 = 2 * times[0] + times[i] + times[i - 1];

        time += min(option1, option2);
        i -= 2;
    }


    if (i == 2) {
        time += times[0] + times[1] + times[2];
    } else if (i == 1) {
        time += times[1];
    } else if (i == 0) {
        time += times[0];
    }

    out << time << endl;
    return 0;
}
