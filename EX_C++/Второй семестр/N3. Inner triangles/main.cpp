#include <iostream>

using namespace std;


long long computeCombination(long long n, long long k) {
    if (k > n) return 0;
    k = min(k, n - k);
    long long combination = 1;
    for (int i = 1; i <= k; ++i) {
        combination *= (n - k + i);
        combination /= i;
    }
    return combination;
}

int main() {
    int redCount, blueCount, greenCount, yellowCount;
    cin >> redCount >> blueCount >> greenCount >> yellowCount;

    int totalPoints = 4 + redCount + blueCount + greenCount + yellowCount;


    int redPoints    = redCount + 2;
    int bluePoints   = blueCount + 2;
    int greenPoints  = greenCount + 2;
    int yellowPoints = yellowCount + 2;


    long long allTriangles = computeCombination(totalPoints, 3);

    long long degenerateTriangles = computeCombination(redPoints, 3)
                                  + computeCombination(bluePoints, 3)
                                  + computeCombination(greenPoints, 3)
                                  + computeCombination(yellowPoints, 3);


    long long validTriangles = allTriangles - degenerateTriangles;

    cout << validTriangles << "\n";
    return 0;
}
