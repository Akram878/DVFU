#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct AVLNode {
    double key;
    int height;
    int size;  // عدد العقد في الشجرة الفرعية هنا
    AVLNode* left;
    AVLNode* right;

    AVLNode(double k) : key(k), height(1), size(1), left(nullptr), right(nullptr) {}
};

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int size(AVLNode* node) {
    return node ? node->size : 0;
}

int balanceFactor(AVLNode* node) {
    return height(node->left) - height(node->right);
}

void updateNode(AVLNode* node) {
    if (node) {
        node->height = 1 + max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right);
    }
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateNode(y);
    updateNode(x);
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateNode(x);
    updateNode(y);
    return y;
}

AVLNode* balance(AVLNode* node) {
    updateNode(node);
    int bf = balanceFactor(node);

    if (bf > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// دالة لإدخال المفتاح مع حساب عدد العقد الأكبر من المفتاح الحالي
// وعدد الانعكاسات نضيفه في count
AVLNode* insert(AVLNode* node, double key, long long& count) {
    if (!node) return new AVLNode(key);

    if (key > node->key) {
        // كل العقد في اليمين + العقدة الحالية أصغر من key
        count += 1 + size(node->right);
        node->left = insert(node->left, key, count);
    } else {
        node->right = insert(node->right, key, count);
    }

    return balance(node);
}


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int N;
    fin >> N;

    // قراء الطول فقط لأن الأسماء غير مهمة هنا لحساب الانعكاسات
    double* heights = new double[N];
    for (int i = 0; i < N; ++i) {
        fin >> heights[i];
        fin.ignore(); // لتجاهل الفراغ قبل الاسم
        string dummy;
        getline(fin, dummy); // قراءة الاسم فقط وتجاهله
    }

    AVLNode* root = nullptr;
    long long inversionCount = 0;


    for (int i = N - 1; i >= 0; --i) {
        root = insert(root, heights[i], inversionCount);
    }

    fout << inversionCount << "\n";

    delete[] heights;
    return 0;
}
