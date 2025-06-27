#include <fstream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 3000;
vector<long long> fact(MAX + 1), inv_fact(MAX + 1);

// دالة حساب القوة السريعة
long long power(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2) result = result * base % MOD;
        base = base * base % MOD;
        exp /= 2;
    }
    return result;
}

// تهيئة المضاريف والعكسيات
void init_factorials() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    inv_fact[MAX] = power(fact[MAX], MOD - 2);
    for (int i = MAX - 1; i >= 0; --i)
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
}

// حساب المعامل الثلاثي
long long multinomial(int a, int b, int c) {
    int total = a + b + c;
    return fact[total] * inv_fact[a] % MOD * inv_fact[b] % MOD * inv_fact[c] % MOD;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int xM, yM, zM, xB, yB, zB;
    fin >> xM >> yM >> zM >> xB >> yB >> zB;

    int dx = abs(xM - xB);
    int dy = abs(yM - yB);
    int dz = abs(zM - zB);

    init_factorials();
    long long result = multinomial(dx, dy, dz);
    fout << result << "\n";

    return 0;
}
