#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    int N, X, Y, MAX = 0;
    int Street[101] = {0}; // مصفوفة تمثل الشارع (من 0 إلى 100 متر)

    input >> N;
    for (int i = 0; i < N; i++) {
        input >> X >> Y;
        int start = (X - Y > 0) ? X - Y : 0; // بداية الإضاءة
        int end = (X + Y > 100) ? 100 : X + Y; // نهاية الإضاءة
        for (int j = start; j < end; j++) { // زيادة العد في المناطق المضاءة
            Street[j]++;
        }
    }

    // إيجاد القيمة القصوى في المصفوفة
    for (int i = 0; i < 101; i++) {
        MAX = (MAX < Street[i]) ? Street[i] : MAX;
    }

    output << MAX;
    return 0;
}
