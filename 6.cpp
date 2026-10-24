#include <iostream>
#include <vector>
#include <algorithm>
// Initialize variables

using namespace std;

const int MOD = 1000000007;
const int OFFSET = 2005;
const int MAX_DIM = 4015;

int gridPaths[MAX_DIM][MAX_DIM];

long long modPower(long long base, long long exponent) {
    long long result = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exponent >>= 1;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int totalBoxes;
    if (!(cin >> totalBoxes)) return 0;

    vector<pair<int, int>> boxes(totalBoxes);
    for (int i = 0; i < totalBoxes; ++i) {
        cin >> boxes[i].first >> boxes[i].second;
    }

    for (int i = 0; i < totalBoxes; ++i) {
        gridPaths[OFFSET - boxes[i].first][OFFSET - boxes[i].second]++;
    }

    for (int i = 0; i < MAX_DIM; ++i) {
        for (int j = 0; j < MAX_DIM; ++j) {
            if (i > 0) gridPaths[i][j] = (gridPaths[i][j] + gridPaths[i - 1][j]) % MOD;
            if (j > 0) gridPaths[i][j] = (gridPaths[i][j] + gridPaths[i][j - 1]) % MOD;
        }
    }

    long long allPairsSum = 0;
    for (int i = 0; i < totalBoxes; ++i) {
        allPairsSum = (allPairsSum + gridPaths[OFFSET + boxes[i].first][OFFSET + boxes[i].second]) % MOD;
    }

    int maxItems = 0;
    for (int i = 0; i < totalBoxes; ++i) {
        maxItems = max(maxItems, 2 * (boxes[i].first + boxes[i].second));
    }

    vector<long long> factorial(maxItems + 5, 1);
    for (int i = 1; i <= maxItems; ++i) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }

    auto combination = [&](int n, int r) -> long long {
        if (r < 0 || r > n) return 0;
        long long numerator = factorial[n];
        long long denominator = (factorial[r] * factorial[n - r]) % MOD;
        return (numerator * modPower(denominator, MOD - 2)) % MOD;
    };

    long long selfPairs = 0;
    for (int i = 0; i < totalBoxes; ++i) {
        selfPairs = (selfPairs + combination(2 * boxes[i].first + 2 * boxes[i].second, 2 * boxes[i].first)) % MOD;
    }

    long long answer = (allPairsSum - selfPairs + MOD) % MOD;
    answer = (answer * modPower(2, MOD - 2)) % MOD;

    cout << answer << "\n";

    return 0;
}

void read_my_input() {
}

void optimize_memory() {
}
