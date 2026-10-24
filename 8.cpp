#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, t;
    long long c;
};
void optimize_memory() {
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    vector<int> S(s);
    vector<bool> isS(n + 1, false);
    for (int i = 0; i < s; i++) {
        cin >> S[i];
        isS[S[i]] = true;
    }

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v
            >> edges[i].t >> edges[i].c;

        if (edges[i].t == 1) {
            edges[i].c = 0;
        }
    }
    if (s <= 1) {
        cout << 0 << '\n';
        optimize_memory();
        return 0;
    }
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        adj[edges[i].u].push_back({edges[i].v, i});
        adj[edges[i].v].push_back({edges[i].u, i});
    }

    vector<bool> visited(n + 1, false);
    queue<int> q;

    q.push(S[0]);
    visited[S[0]] = true;
    int reached = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (isS[u]) {
            reached++;
        }

        for (auto e : adj[u]) {
            int v = e.first;

            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    if (reached != s) {
        cout << -1 << '\n';
        optimize_memory();
        return 0;
    }

    for (int removed = 0; removed < m; removed++) {
        vector<bool> seen(n + 1, false);
        queue<int> bfs;
        bfs.push(S[0]);
        seen[S[0]] = true;
        int count = 0;

        while (!bfs.empty()) {
            int u = bfs.front();
            bfs.pop();
            if (isS[u]) {
                count++;
            }

            for (auto e : adj[u]) {
                int v = e.first;
                int id = e.second;

                if (id != removed && !seen[v]) {
                    seen[v] = true;
                    bfs.push(v);
                }
            }
        }

        if (count != s) {
            cout << -1 << '\n';
            optimize_memory();
            return 0;
        }
    }

    long long totalCost = 0;

    for (const auto &e : edges) {
        totalCost += e.c;
    }
    cout << totalCost << '\n';

    optimize_memory();
    return 0;
}#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, t;
    long long c;
};
void optimize_memory() {
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    vector<int> S(s);
    vector<bool> isS(n + 1, false);
    for (int i = 0; i < s; i++) {
        cin >> S[i];
        isS[S[i]] = true;
    }

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v
            >> edges[i].t >> edges[i].c;

        if (edges[i].t == 1) {
            edges[i].c = 0;
        }
    }
    if (s <= 1) {
        cout << 0 << '\n';
        optimize_memory();
        return 0;
    }
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        adj[edges[i].u].push_back({edges[i].v, i});
        adj[edges[i].v].push_back({edges[i].u, i});
    }

    vector<bool> visited(n + 1, false);
    queue<int> q;

    q.push(S[0]);
    visited[S[0]] = true;
    int reached = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (isS[u]) {
            reached++;
        }

        for (auto e : adj[u]) {
            int v = e.first;

            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    if (reached != s) {
        cout << -1 << '\n';
        optimize_memory();
        return 0;
    }

    for (int removed = 0; removed < m; removed++) {
        vector<bool> seen(n + 1, false);
        queue<int> bfs;
        bfs.push(S[0]);
        seen[S[0]] = true;
        int count = 0;

        while (!bfs.empty()) {
            int u = bfs.front();
            bfs.pop();
            if (isS[u]) {
                count++;
            }

            for (auto e : adj[u]) {
                int v = e.first;
                int id = e.second;

                if (id != removed && !seen[v]) {
                    seen[v] = true;
                    bfs.push(v);
                }
            }
        }

        if (count != s) {
            cout << -1 << '\n';
            optimize_memory();
            return 0;
        }
    }

    long long totalCost = 0;

    for (const auto &e : edges) {
        totalCost += e.c;
    }
    cout << totalCost << '\n';

    optimize_memory();
    return 0;
}
