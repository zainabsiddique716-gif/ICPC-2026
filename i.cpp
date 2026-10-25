
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;
const ll INF = LLONG_MAX / 4;

struct Edge {
    int to, id;
    ll w;
};

struct Road {
    int u, v;
    ll w;
};

int N, M, S, T;
vector<vector<Edge> > adj;
vector<Road> roads;

vector<ll> dijkstra(int src, vector<int>& parent,
    vector<int>& parentEdge) {
    vector<ll> dist(N + 1, INF);
    parent.assign(N + 1, -1);
    parentEdge.assign(N + 1, -1);

    priority_queue<pair<ll, int>,
        vector<pair<ll, int> >,
        greater<pair<ll, int> > > pq;

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist[u])
            continue;

        for (int i = 0; i < (int)adj[u].size(); i++) {
            Edge e = adj[u][i];

            if (d + e.w < dist[e.to]) {
                dist[e.to] = d + e.w;
                parent[e.to] = u;
                parentEdge[e.to] = e.id;
                pq.push(make_pair(dist[e.to], e.to));
            }
        }
    }

    return dist;
}

struct SegmentTree {
    int n;
    vector<ll> lazy;

    SegmentTree(int size) {
        n = size;
        lazy.assign(4 * n + 5, INF);
    }

    void update(int node, int l, int r,
        int ql, int qr, ll val) {
        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            lazy[node] = min(lazy[node], val);
            return;
        }

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r,
            ql, qr, val);
    }

    void update(int l, int r, ll val) {
        if (l <= r)
            update(1, 0, n - 1, l, r, val);
    }

    ll query(int node, int l, int r,
        int idx, ll best) {
        best = min(best, lazy[node]);

        if (l == r)
            return best;

        int mid = (l + r) / 2;

        if (idx <= mid)
            return query(node * 2, l, mid, idx, best);

        return query(node * 2 + 1, mid + 1, r,
            idx, best);
    }

    ll query(int idx) {
        return query(1, 0, n - 1, idx, INF);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> S >> T;

    adj.resize(N + 1);
    roads.resize(M);

    for (int i = 0; i < M; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        roads[i] = { u, v, w };

        adj[u].push_back({ v, i, w });
        adj[v].push_back({ u, i, w });
    }

    vector<int> parS, edgeS, parT, edgeT;

    vector<ll> distS = dijkstra(S, parS, edgeS);
    vector<ll> distT = dijkstra(T, parT, edgeT);

    vector<int> path;
    vector<int> pathEdge;

    int cur = T;

    while (cur != S) {
        path.push_back(cur);
        pathEdge.push_back(edgeS[cur]);
        cur = parS[cur];
    }

    path.push_back(S);

    reverse(path.begin(), path.end());
    reverse(pathEdge.begin(), pathEdge.end());

    int K = (int)path.size() - 1;
    ll D = distS[T];

    vector<int> pos(N + 1, -1);

    for (int i = 0; i <= K; i++)
        pos[path[i]] = i;

    vector<char> onPath(M, 0);

    for (int i = 0; i < K; i++)
        onPath[pathEdge[i]] = 1;

    vector<int> orderS(N), orderT(N);

    for (int i = 0; i < N; i++) {
        orderS[i] = i + 1;
        orderT[i] = i + 1;
    }

    sort(orderS.begin(), orderS.end(),
        [&](int a, int b) {
            return distS[a] < distS[b];
        });

    sort(orderT.begin(), orderT.end(),
        [&](int a, int b) {
            return distT[a] < distT[b];
        });

    vector<int> a(N + 1, -1);

    for (int i = 0; i <= K; i++)
        a[path[i]] = i;

    for (int v : orderS) {
        if (a[v] != -1)
            continue;

        if (parS[v] != -1)
            a[v] = a[parS[v]];
    }

    vector<int> b(N + 1, -1);

    for (int i = 0; i <= K; i++)
        b[path[i]] = i;

    for (int v : orderT) {
        if (b[v] != -1)
            continue;

        if (parT[v] != -1)
            b[v] = b[parT[v]];
    }

    SegmentTree seg(K);

    for (int i = 0; i < M; i++) {
        if (onPath[i])
            continue;

        int u = roads[i].u;
        int v = roads[i].v;
        ll w = roads[i].w;

        if (a[u] != -1 && b[v] != -1 && a[u] < b[v]) {
            ll candidate = distS[u] + w + distT[v];
            seg.update(a[u], b[v] - 1, candidate);
        }

        if (a[v] != -1 && b[u] != -1 && a[v] < b[u]) {
            ll candidate = distS[v] + w + distT[u];
            seg.update(a[v], b[u] - 1, candidate);
        }
    }

    vector<ll> replacement(K, INF);

    for (int i = 0; i < K; i++)
        replacement[i] = seg.query(i);

    vector<ll> answer(M, D);

    for (int i = 0; i < K; i++)
        answer[pathEdge[i]] =
        (replacement[i] >= INF ? -1 : replacement[i]);

    for (int i = 0; i < M; i++)
        cout << answer[i] << '\n';

    return 0;
}
 
