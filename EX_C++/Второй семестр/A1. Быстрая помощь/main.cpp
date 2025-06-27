#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // إنشاء مصفوفات مؤقتة
    vector<int> L(n1), R(n2);

    // نسخ البيانات إلى المصفوفات المؤقتة
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // دمج المصفوفات المؤقتة مع الحفاظ على الترتيب
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

    // نسخ العناصر المتبقية من L (إذا وجدت)
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // نسخ العناصر المتبقية من R (إذا وجدت)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// الدالة الرئيسية لـ Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // تقسيم المصفوفة إلى نصفين وترتيب كل نصف
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // دمج النصفين المُرتبين
        merge(arr, left, mid, right);
    }
}


using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int N, L;
    input >> N >> L;

    vector<int> flightTimes(N);
    for (int i = 0; i < N; ++i) {
        input >> flightTimes[i];
    }

   mergeSort(flightTimes, 0, flightTimes.size() - 1); // ترتيب تصاعدي لزمن الطيران

    int currentTime = 0; // الوقت الذي تنتهي فيه آخر عملية تفريغ
    for (int i = 0; i < N; ++i) {
        currentTime = max(currentTime, flightTimes[i]) + L;
    }

    output << currentTime << endl;

    input.close();
    output.close();
    return 0;
}
