#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n;
long long M;

bool build(vector<long long>& r, vector<long long>& t) {
    if (n == 1) {
        t[0] = 1;
        return true;
    }
    if (n == 2) {
        long long lo = min(r[0], r[1]), hi = max(r[0], r[1]);
        if (hi - lo < 2) return false;
        for (int i = 0; i < 2; i++) t[i] = (r[i] == lo) ? hi - lo - 1 : 1;
        return true;
    }
    vector<pair<long long, int>> p(n);
    for (int i = 0; i < n; i++) p[i] = make_pair(r[i], i);
    sort(p.begin(), p.end());
    int h = n / 2;
    long long k;
    if (n % 2 == 1) k = p[h].first;
    else if (p[h].first - p[h - 1].first >= 2) k = p[h - 1].first + 1;
    else k = p[h - 1].first;
    vector<int> L, U;
    int z = -1;
    for (int i = n - 1; i >= 0; i--)
        if (p[i].first < k) L.push_back(p[i].second);
    for (int i = 0; i < n; i++) {
        if (p[i].first > k) U.push_back(p[i].second);
        if (p[i].first == k) z = p[i].second;
    }
    if (L.size() == U.size()) {
        for (int i = 0; i < (int)L.size(); i++) {
            t[L[i]] = r[U[i]] - k;
            t[U[i]] = k - r[L[i]];
        }
    } else {
        int e = U[0], um = U.back();
        long long ymax = r[um] - k;
        vector<long long> Y;
        for (int i = 1; i + 1 < (int)U.size(); i++) Y.push_back(r[U[i]] - k);
        Y.push_back(ymax + 1);
        sort(Y.begin(), Y.end());
        int T = -1;
        for (int i = 0; i < (int)L.size(); i++) {
            if (!binary_search(Y.begin(), Y.end(), k - r[L[i]])) {
                T = L[i];
                break;
            }
        }
        if (T == -1) return false;
        long long x = k - r[T];
        t[T] = ymax + 1;
        t[e] = x;
        t[um] = x;
        int j = 1;
        for (int i = 0; i < (int)L.size(); i++) {
            if (L[i] == T) continue;
            t[L[i]] = r[U[j]] - k;
            t[U[j]] = k - r[L[i]];
            j++;
        }
    }
    if (z != -1) {
        vector<int> cnt(n + 2, 0);
        for (int i = 0; i < n; i++)
            if (i != z && t[i] <= n + 1) cnt[t[i]]++;
        int v = 1;
        while (cnt[v] > 0) v++;
        t[z] = v;
    }
    return true;
}

int main() {
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d %lld", &n, &M);
        vector<long long> r(n), t(n);
        for (int i = 0; i < n; i++) scanf("%lld", &r[i]);
        bool ok = build(r, t);
        if (!ok) {
            vector<long long> r2(n);
            for (int i = 0; i < n; i++) r2[i] = M + 1 - r[i];
            ok = build(r2, t);
        }
        if (!ok) {
            printf("-1\n");
            continue;
        }
        for (int i = 0; i < n; i++) printf("%lld%c", t[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
