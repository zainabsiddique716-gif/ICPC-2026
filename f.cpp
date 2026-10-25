
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

const int LIMIT = 6776;
const int HALF = LIMIT / 2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;

    vector<vector<int> > adj(N + 1);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> ds(N + 1, -1), dt(N + 1, -1);
    string ans;
    ans.reserve(Q);

    vector<int> qs, qt;
    qs.reserve(N);
    qt.reserve(N);

    for (int qi = 0; qi < Q; qi++) {
        int s, t;
        cin >> s >> t;

        if (s == t) {
            ans += '1';
            continue;
        }

        fill(ds.begin(), ds.end(), -1);
        fill(dt.begin(), dt.end(), -1);

        queue<int> qS, qT;

        ds[s] = 0;
        dt[t] = 0;
        qS.push(s);
        qT.push(t);

        bool found = false;

        while (!qS.empty() && !qT.empty() && !found) {
            // Expand one complete layer from the
            // smaller frontier.
            bool fromS = qS.size() <= qT.size();
            queue<int>& q = fromS ? qS : qT;
            vector<int>& own = fromS ? ds : dt;
            vector<int>& other = fromS ? dt : ds;

            int layerSize = (int)q.size();

            while (layerSize-- > 0 && !found) {
                int u = q.front();
                q.pop();

                if (own[u] >= HALF)
                    continue;

                for (int v : adj[u]) {
                    // Check the other search BEFORE
                    // skipping an already visited node.
                    if (other[v] != -1 &&
                        own[u] + 1 + other[v] <= LIMIT) {
                        found = true;
                        break;
                    }

                    if (own[v] == -1) {
                        own[v] = own[u] + 1;

                        if (other[v] != -1 &&
                            own[v] + other[v] <= LIMIT) {
                            found = true;
                            break;
                        }

                        q.push(v);
                    }
                }
            }
        }

        ans += (found ? '1' : '0');
    }

    cout << ans << '\n';
    return 0;
}
