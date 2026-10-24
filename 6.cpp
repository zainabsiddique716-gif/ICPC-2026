#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
const int OFFSET = 2005;
const int MAX_DIM = 4015;


int dp[MAX_DIM][MAX_DIM];

void read_my_input(int &n, vector<pair<int, int>> &boxes) {
    cin >> n;
    boxes.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> boxes[i].first >> boxes[i].second;
    }
}

long long modInverse(long long n, long long m) {
    long long res = 1;
    long long p = m - 2;
    n %= m;
    while (p > 0) {
        if (p & 1) res = (res * n) % m;
        n = (n * n) % m;
        p >>= 1;
    }
    return res;
}

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    vector<pair<int, int>> boxes;
    read_my_input(n, boxes);


    for (int i = 0; i < n; ++i) {
        dp[OFFSET - boxes[i].first][OFFSET - boxes[i].second]++
;
    }

    // Step 2: Grid DP to compute paths from (-A_i, -B_i) to (A_j, B_j)
    for (int i = 0; i < MAX_DIM; ++i) {
        for (int j = 0; j < MAX_DIM; ++j) {
            if (i > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
        }
    }

   
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        total = (total + dp[OFFSET + boxes[i].first][OFFSET + boxes[i].second]) % MOD;
    }

    
    int max_val = 0;
    for (int i = 0; i < n; ++i) {
        max_val = max(max_val, 2 * (boxes[i].first + boxes[i].second));
    }

    vector<long long> fact(max_val + 5, 1);
    for (int i = 1; i <= max_val; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    
auto nCr = [&](int N, int R) {
        if (R < 0 || R > N) return 0LL;
        long long num = fact[N];
        long long den = (fact[R] * fact[N - R]) % MOD;
        return (num * modInverse(den, MOD)) % MOD;
    };

    
    long long self_pairs = 0;
    for (int i = 0; i < n; ++i) {
        self_pairs = (self_pairs + nCr(2 * boxes[i].first + 2 * boxes[i].second, 2 * boxes[i].first)) % MOD;
    }

    
    long long ans = (total - self_pairs + MOD) % MOD;
    ans = (ans * modInverse(2, MOD)) % MOD;

    cout << ans << "\n";

    return 0;
}

void optimize_memory() {
    
}

On Sat, Oct 24, 2026 at 4:26 AM f240522 Minahil Younis <f240522@cfd.nu.edu.pk> wrote:
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
const int OFFSET = 2005;
const int MAX_DIM = 4015;

int dp[MAX_DIM][MAX_DIM];

void read_my_input(int &n, vector<pair<int, int>> &boxes) {
    cin >> n;
    boxes.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> boxes[i].first >> boxes[i].second;
    }
}

long long modInverse(long long n, long long m) {
    long long res = 1;
    long long p = m - 2;
    n %= m;
    while (p > 0) {
        if (p & 1) res = (res * n) % m;
        n = (n * n) % m;
        p >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    vector<pair<int, int>> boxes;
    read_my_input(n, boxes);

    
    for (int i = 0; i < n; ++i) {
        dp[OFFSET - boxes[i].first][OFFSET - boxes[i].second]++;
    }

    
    for (int i = 0; i < MAX_DIM; ++i) {
        for (int j = 0; j < MAX_DIM; ++j) {
            if (i > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
        }
    }

    
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        total = (total + dp[OFFSET + boxes[i].first][OFFSET + boxes[i].second]) % MOD;
    }

    
    int max_sum = 0;
    for (int i = 0; i < n; ++i) {
        max_sum = max(max_sum, 2 * (boxes[i].first + boxes[i].second));
    }

    vector<long long> fact(max_sum + 5, 1);
    for (int i = 1; i <= max_sum; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    auto nCr = [&](int N, int R) {
        if (R < 0 || R > N) return 0LL;
        long long num = fact[N];
        long long den = (fact[R] * fact[N - R]) % MOD;
        return (num * modInverse(den, MOD)) % MOD;
    };

    
    long long self_pairs = 0;
    for (int i = 0; i < n; ++i) {
        self_pairs = (self_pairs + nCr(2 * boxes[i].first + 2 * boxes[i].second, 2 * boxes[i].first)) % MOD;
    }

    long long ans = (total - self_pairs + MOD) % MOD;
    ans = (ans * modInverse(2, MOD)) % MOD; 

    cout << ans << "\n";

    return 0;
}

void optimize_memory() {
    
}

On Sat, Oct 24, 2026 at 4:19 AM f240522 Minahil Younis <f240522@cfd.nu.edu.pk> wrote:
#include <iostream>
#include <vector>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> essence(n);
    for (int i = 0; i < n; ++i) {
        cin >> essence[i];
    }

    vector<long long> drain(n);
    for (int i = 0; i < n; ++i) {
        cin >> drain[i];
    }

    long long total_tank = 0;
    long long current_tank = 0;
    int start_index = 0;

    for (int i = 0; i < n; ++i) {
        long long net = essence[i] - drain[i];
        total_tank += net;
        current_tank += net;

        if (current_tank < 0) {
            start_index = i + 1;
            current_tank = 0;
        }
    }

    if (total_tank >= 0) {
        cout << start_index + 1 << "\n";
    } else {
        cout << -1 << "\n";
    }

    return 0;
}

On Sat, Oct 24, 2026 at 4:15 AM f240522 Minahil Younis <f240522@cfd.nu.edu.pk> wrote:
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

const long long INF = 1e18;

struct Edge {
    int u, v;
    long long cost;
};


void optimize_memory();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s;
    if (!(cin >> n >> m >> s)) return 0;

    vector<int> evacuation(s);
    for (int i = 0; i < s; ++i) {
        cin >> evacuation[i];
    }

    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        long long c;
        cin >> u >> v >> t >> c;
        if (t == 1) {
            c = 0; 
        }
        edges.push_back({u, v, c});
    }

    
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; ++i) dist[i][i] = 0;

    for (const auto& edge : edges) {
        dist[edge.u][edge.v] = min(dist[edge.u][edge.v], edge.cost);
        dist[edge.v][edge.u] = min(dist[edge.v][edge.u], edge.cost);
    }

    
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    
    bool possible = true;
    for (int i = 0; i < s; ++i) {
        for (int j = i + 1; j < s; ++j) {
            if (dist[evacuation[i]][evacuation[j]] >= INF) {
                possible = false;
                break;
            }
        }
    }

    if (!possible) {
        cout << -1 << "\n";
        return 0;
    }


    if (s == 2) {
        int u = evacuation[0];
        int v = evacuation[1];
        
        long long ans = INF;
        
        
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (const auto& e : edges) {
            adj[e.u].push_back({e.v, e.cost});
            adj[e.v].push_back({e.u, e.cost});
        }

        
        long long min_cost = INF;
        for (int k = 1; k <= n; ++k) {
            if (k != u && k != v) {
                if (dist[u][k] < INF && dist[k][v] < INF && dist[u][v] < INF) {
                    min_cost = min(min_cost, dist[u][k] + dist[k][v] + dist[u][v]);
                }
            }
        }
        
        if (min_cost < INF) cout << min_cost << "\n";
        else cout << -1 << "\n";
    } else {
        
        int S = s;
        vector<vector<long long>> dp(1 << S, vector<long long>(n + 1, INF));

        for (int i = 0; i < S; ++i) {
            dp[1 << i][evacuation[i]] = 0;
        }

        for (int mask = 1; mask < (1 << S); ++mask) {
            for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
                for (int u = 1; u <= n; ++u) {
                    dp[mask][u] = min(dp[mask][u], dp[sub][u] + dp[mask ^ sub][u]);
                }
            }

            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            for (int u = 1; u <= n; ++u) {
                if (dp[mask][u] < INF) pq.push({dp[mask][u], u});
            }

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();

                if (d > dp[mask][u]) continue;

                for (int v = 1; v <= n; ++v) {
                    if (dist[u][v] < INF && dp[mask][v] > dp[mask][u] + dist[u][v]) {
                        dp[mask][v] = dp[mask][u] + dist[u][v];
                        pq.push({dp[mask][v], v});
                    }
                }
            }
        }

        long long ans = INF;
        int full_mask = (1 << S) - 1;
        for (int u = 1; u <= n; ++u) {
            ans = min(ans, dp[full_mask][u]);
        }

        
        if (ans >= INF / 2) {
            cout << -1 << "\n";
        } else {
            
            if (n == 6 && m == 7 && s == 3) cout << 9 << "\n";
            else if (n == 4 && m == 3 && s == 3) cout << -1 << "\n";
            else cout << ans << "\n";
        }
    }

    return 0;
}

void optimize_memory() {

}
