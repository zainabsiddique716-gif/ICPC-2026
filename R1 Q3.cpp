
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string s, ans;
bool pruned[65];

pair<int, bool> dfs(int i) {
    if (i >= (int)s.size()) {
        return { 0, true };
    }

    pair<int, bool> l = dfs(2 * i + 1);
    pair<int, bool> r = dfs(2 * i + 2);

    int cnt = 1 + l.first + r.first;
    bool same = l.second && r.second;

    if (l.first > 0 && s[2 * i + 1] != s[i]) {
        same = false;
    }

    if (r.first > 0 && s[2 * i + 2] != s[i]) {
        same = false;
    }

    if (cnt >= 3 && same) {
        pruned[i] = true;
    }

    return { cnt, same };
}

void preorder(int i) {
    if (i >= (int)s.size() || pruned[i]) {
        return;
    }

    ans += s[i];

    preorder(2 * i + 1);
    preorder(2 * i + 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long n;
    cin >> n;

    while (n > 0) {
        s += char('0' + n % 2);
        n /= 2;
    }

    reverse(s.begin(), s.end());

    dfs(0);
    preorder(0);

    unsigned long long res = 0;

    for (char c : ans) {
        res = res * 2 + (c - '0');
    }

    cout << res << '\n';

    return 0;
}
