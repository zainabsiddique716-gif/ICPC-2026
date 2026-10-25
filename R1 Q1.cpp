
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<unsigned long long> A(n), B(n);

    for (int j = 0; j < n; j++) {
        cin >> A[j] >> B[j];
    }

    vector<int> patternA(k, 0), patternB(k, 0);

    for (int i = 0; i < k; i++) {
        int countA = 0;
        int countB = 0;

        for (int j = 0; j < n; j++) {
            countA += (A[j] >> i) & 1ULL;
            countB += (B[j] >> i) & 1ULL;
        }

        // Counts alone do not uniquely identify a bit pattern.
        // Encode the complete pattern using its position in a list.
    }

    vector<vector<unsigned long long> > patA(
        k, vector<unsigned long long>((n + 63) / 64, 0)
    );

    vector<vector<unsigned long long> > patB(
        k, vector<unsigned long long>((n + 63) / 64, 0)
    );

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if ((A[j] >> i) & 1ULL) {
                patA[i][j / 64] |= 1ULL << (j % 64);
            }

            if ((B[j] >> i) & 1ULL) {
                patB[i][j / 64] |= 1ULL << (j % 64);
            }
        }
    }

    vector<int> orderA(k), orderB(k);

    for (int i = 0; i < k; i++) {
        orderA[i] = i;
        orderB[i] = i;
    }

    sort(orderA.begin(), orderA.end(),
        [&](int x, int y) {
            return patA[x] < patA[y];
        });

    sort(orderB.begin(), orderB.end(),
        [&](int x, int y) {
            return patB[x] < patB[y];
        });

    vector<int> pi(k, -1);

    int i = 0, j = 0;

    while (i < k && j < k) {
        if (patA[orderA[i]] < patB[orderB[j]]) {
            cout << -1 << '\n';
            return 0;
        }

        if (patB[orderB[j]] < patA[orderA[i]]) {
            cout << -1 << '\n';
            return 0;
        }

        int iEnd = i;
        int jEnd = j;

        while (iEnd < k &&
            patA[orderA[iEnd]] == patA[orderA[i]]) {
            iEnd++;
        }

        while (jEnd < k &&
            patB[orderB[jEnd]] == patB[orderB[j]]) {
            jEnd++;
        }

        if (iEnd - i != jEnd - j) {
            cout << -1 << '\n';
            return 0;
        }

        vector<int> from, to;

        for (int x = i; x < iEnd; x++) {
            from.push_back(orderA[x]);
        }

        for (int x = j; x < jEnd; x++) {
            to.push_back(orderB[x]);
        }

        sort(from.begin(), from.end());
        sort(to.begin(), to.end());

        for (int x = 0; x < (int)from.size(); x++) {
            pi[from[x]] = to[x];
        }

        i = iEnd;
        j = jEnd;
    }

    if (i != k || j != k) {
        cout << -1 << '\n';
        return 0;
    }

    for (int x = 0; x < k; x++) {
        if (x > 0) cout << ' ';
        cout << pi[x];
    }

    cout << '\n';

    return 0;
}
