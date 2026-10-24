
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Initialize variables

const long long MOD = 1000000007LL;

long long modPower(long long base, long long exponent) {
    long long result = 1;

    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % MOD;
        }

        base = base * base % MOD;
        exponent >>= 1;
    }

    return result;
}

void optimize_memory() {
}

void read_my_input() {
    int totalBoxes;
    cin >> totalBoxes;

    vector<int> countA(totalBoxes);
    vector<int> countB(totalBoxes);

    for (int i = 0; i < totalBoxes; i++) {
        cin >> countA[i] >> countB[i];
    }

    int maxTotal = 0;

    for (int i = 0; i < totalBoxes; i++) {
        maxTotal = max(maxTotal, countA[i] + countB[i]);
    }

    vector<long long> factorial(2 * maxTotal + 1, 1);
    vector<long long> inverseFactorial(2 * maxTotal + 1, 1);

    for (int i = 1; i <= 2 * maxTotal; i++) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }

    inverseFactorial[2 * maxTotal] =
        modPower(factorial[2 * maxTotal], MOD - 2);

    for (int i = 2 * maxTotal; i >= 1; i--) {
        inverseFactorial[i - 1] =
            inverseFactorial[i] * i % MOD;
    }

    long long answer = 0;

    for (int i = 0; i < totalBoxes; i++) {
        for (int j = i + 1; j < totalBoxes; j++) {
            int totalA = countA[i] + countA[j];
            int totalB = countB[i] + countB[j];
            int totalItems = totalA + totalB;

            long long ways = factorial[totalItems];

            ways = ways * inverseFactorial[totalA] % MOD;
            ways = ways * inverseFactorial[totalB] % MOD;

            answer = (answer + ways) % MOD;
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_my_input();
    optimize_memory();

    return 0;
}
