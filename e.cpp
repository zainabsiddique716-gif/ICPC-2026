
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;

int N, Q;
long long P[MAXN];
int nxt[MAXN];
int bit[MAXN];

vector<int> ending[MAXN];
vector<pair<int, int> > queries[MAXN];

void update(int i, int val) {
    while (i <= N) {
        bit[i] += val;
        i += i & -i;
    }
}

int query(int i) {
    int sum = 0;
    while (i > 0) {
        sum += bit[i];
        i -= i & -i;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;

    for (int i = 1; i <= N; i++) {
        cin >> P[i];
    }

    vector<int> st;
    st.reserve(N);

    for (int i = N; i >= 1; i--) {
        while (!st.empty() && P[st.back()] <= P[i]) {
            st.pop_back();
        }

        if (st.empty()) {
            nxt[i] = N + 1;
        }
        else {
            nxt[i] = st.back();
        }

        st.push_back(i);

        if (nxt[i] <= N) {
            ending[nxt[i]].push_back(i);
        }
    }

    for (int i = 0; i < Q; i++) {
        int L, R;
        cin >> L >> R;
        queries[R].push_back({ L, i });
    }

    vector<int> ans(Q);

    for (int R = 1; R <= N; R++) {
        update(R, 1);

        for (int i : ending[R]) {
            update(i, -1);
        }

        for (auto qu : queries[R]) {
            int L = qu.first;
            int id = qu.second;

            ans[id] = query(R) - query(L - 1);
        }
    }

    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
