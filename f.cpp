#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int LIMIT = 6776;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;

    vector<vector<int>> adj(N + 1);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int, int>> queries(Q);
    vector<vector<int>> queriesBySource(N + 1);

    for (int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;
        queries[i] = { u, v };
        queriesBySource[u].push_back(i);
    }

    string ans(Q, '0');
    vector<int> dist(N + 1);
    vector<int> seen(N + 1, 0);
    int stamp = 0;

    for (int s = 1; s <= N; s++) {
        if (queriesBySource[s].empty())
            continue;

        ++stamp;
        queue<int> q;
        q.push(s);
        seen[s] = stamp;
        dist[s] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (dist[u] == LIMIT)
                continue;

            for (int v : adj[u]) {
                if (seen[v] == stamp)
                    continue;

                seen[v] = stamp;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

        for (int id : queriesBySource[s]) {
            int v = queries[id].second;

            if (seen[v] == stamp && dist[v] <= LIMIT)
                ans[id] = '1';
        }
    }

    cout << ans << '\n';

    return 0;
}
