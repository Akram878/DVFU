#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// تحويل الحرف إلى رقم في المدى [0, 51]
int charIndex(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';         // A-Z ⟶ 0-25
    if (c >= 'a' && c <= 'z') return 26 + (c - 'a');   // a-z ⟶ 26-51
    return -1; // حالة غير متوقعة (ليست حرفاً)
}

// الترتيب حسب موضع حرف معين (pos = 0 أو 1 أو 2)
void bucketSortLevel(vector<string>& words, int pos) {
    vector<vector<string>> buckets(52); // 26 للحروف الكبيرة + 26 للحروف الصغيرة

    for (const string& word : words) {
        int index = charIndex(word[pos]);
        if (index >= 0) {
            buckets[index].push_back(word);
        }
    }

    words.clear();
    for (int i = 0; i < 52; ++i) {
        for (const string& word : buckets[i]) {
            words.push_back(word);
        }
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int N;
    input >> N;

    vector<string> words(N);
    for (int i = 0; i < N; ++i) {
        input >> words[i];
    }

    // الترتيب من الحرف الأخير إلى الأول
    bucketSortLevel(words, 2);
    bucketSortLevel(words, 1);
    bucketSortLevel(words, 0);

    for (const string& word : words) {
        output << word << '\n';
    }

    input.close();
    output.close();
    return 0;
}
