#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;
const ll INF = LLONG_MAX / 4;

static bool halfok(long long w, long long C) {
    return 2 * w >= C;   
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ll Cc, Pc, Cv, Pv;
    cin >> Cc >> Pc >> Cv >> Pv;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }

    vector<ll> dp0(n + 1, INF);
    vector<ll> dp1(n + 1, INF);
    dp0[0] = 0;

    for (int j = 1; j <= n; j++) {
        for (int i = 0; i < j; i++) {
            ll S = pref[j] - pref[i];

            ll bestN = INF;
            ll bestE = INF;

            if (S <= Cc) {
                if (halfok(S, Cc)) bestN = min(bestN, Pc);
                else bestE = min(bestE, Pc);
            }

            if (S <= Cv) {
                if (halfok(S, Cv)) bestN = min(bestN, Pv);
                else bestE = min(bestE, Pv);
            }

            if (bestN < INF) {
                if (dp0[i] < INF) dp0[j] = min(dp0[j], dp0[i] + bestN);
                if (dp1[i] < INF) dp1[j] = min(dp1[j], dp1[i] + bestN);
            }

            if (bestE < INF && dp0[i] < INF) {
                dp1[j] = min(dp1[j], dp0[i] + bestE);
            }
        }
    }

    ll ans = min(dp0[n], dp1[n]);
    if (ans >= INF) cout << -1 << '\n';
    else cout << ans << '\n';

    return 0;
}
