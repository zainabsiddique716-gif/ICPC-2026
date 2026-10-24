#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
