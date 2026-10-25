
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;

using ll = long long;

struct Chord {
    int z, x, y;
    int cnt;
    ll sum;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        const ll INF = LLONG_MAX / 4;

        ll dist[26];
        bool done[26] = {};

        for (int i = 0; i < 26; i++) {
            cin >> dist[i];

            if (dist[i] == -1) {
                dist[i] = INF;
            }
        }

        int m;
        cin >> m;

        vector<Chord> chords(m);
        vector<vector<int> > rev(26);

        for (int i = 0; i < m; i++) {
            char z, x, y;
            cin >> z >> x >> y;

            chords[i] = { z - 'a', x - 'a', y - 'a', 0, 0 };

            rev[x - 'a'].push_back(i);
            rev[y - 'a'].push_back(i);
        }

        priority_queue<
            pair<ll, int>,
            vector<pair<ll, int> >,
            greater<pair<ll, int> >
        > pq;

        for (int i = 0; i < 26; i++) {
            if (dist[i] != INF) {
                pq.push({ dist[i], i });
            }
        }

        while (!pq.empty()) {
            ll d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (done[u] || d != dist[u]) {
                continue;
            }

            done[u] = true;

            for (int id : rev[u]) {
                Chord& c = chords[id];

                c.cnt++;
                c.sum += d;

                if (c.cnt == 2) {
                    if (c.sum < dist[c.z]) {
                        dist[c.z] = c.sum;
                        pq.push({ dist[c.z], c.z });
                    }
                }
            }
        }

        string s;
        cin >> s;

        ll ans = 0;
        bool ok = true;

        for (char c : s) {
            if (dist[c - 'a'] == INF) {
                ok = false;
                break;
            }

            ans += dist[c - 'a'];
        }

        cout << (ok ? ans : -1) << '\n';
    }

    return 0;
}


