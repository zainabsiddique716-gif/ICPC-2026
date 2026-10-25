#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

int digits(ll p) {
    int d = 0;
    while (p > 0) {
        d++;
        p /= 10;
    }
    return d;
}

bool cmp(ll a, ll b) {
    return (ll)digits(a) * a * (b - 1)
        < (ll)digits(b) * b * (a - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        ll M;
        cin >> M;

        ll n = M;
        vector<ll> factors;

        for (ll p = 2; p <= n / p; p++) {
            while (n % p == 0) {
                factors.push_back(p);
                n /= p;
            }
        }

        if (n > 1)
            factors.push_back(n);

        sort(factors.begin(), factors.end(), cmp);

        ll x = M;
        ll ans = 0;

        for (ll p : factors) {
            ans += x * digits(p);
            x /= p;
        }

        cout << ans << '\n';
    }

    return 0;
}
