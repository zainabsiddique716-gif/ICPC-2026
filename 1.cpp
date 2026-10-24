#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Event {
    int u, v;
    long long t;
};

void optimize_memory() {
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Initialize variables
    int n, m, delta;
    cin >> n >> m >> delta;

    vector<Event> events(m);

    for (int i = 0; i < m; i++) {
        cin >> events[i].u >> events[i].v >> events[i].t;
    }

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.t < b.t;
        });

    vector<vector<int>> edge(n, vector<int>(n, 0));

    long long type1 = 0;
    long long type2 = 0;
    long long type3 = 0;

    for (int i = 0; i < m; i++) {
        int a = events[i].u;
        int b = events[i].v;
        long long t3 = events[i].t;

        int left = i - 1;

        while (left >= 0 && t3 - events[left].t <= delta) {
            left--;
        }
        left++;

        for (int j = left; j < i; j++) {
            int x = events[j].u;
            int y = events[j].v;

            for (int k = j + 1; k < i; k++) {
                if (events[k].t <= events[j].t) continue;

                int p = events[k].u;
                int q = events[k].v;

                if (events[k].t - events[j].t > delta) continue;

                if (x == y || p == q || a == b) continue;

                if (y == p && q == x && x != y && y != q && q != x) {
                    if (x != p && y != q && x != q) {
                        type1++;
                    }
                }

                if (x == p && y != q && y == events[k].u) {
                    // No action: handled by the exact pattern check below.
                }

                if (x == a && y == b && p == a && q == b) {
                    // Repeated directed edges cannot form Type 2.
                }
            }
        }
    }

    type1 = 0;
    type2 = 0;
    type3 = 0;

    for (int i = 0; i < m; i++) {
        int a = events[i].u;
        int b = events[i].v;
        long long t1 = events[i].t;

        for (int j = i + 1; j < m; j++) {
            if (events[j].t - t1 > delta) break;

            int c = events[j].u;
            int d = events[j].v;

            if (a == c && b == d) {
                continue;
            }

            for (int k = j + 1; k < m; k++) {
                if (events[k].t - t1 > delta) break;

                int e = events[k].u;
                int f = events[k].v;

                if (a == e && b == f) continue;

                if (a == d && b == c) {
                    // Continue checking patterns independently.
                }

                if (b == c && d == e && f == a &&
                    a != b && a != c && b != c) {
                    type1++;
                }

                if (a == c && b == e && d == f &&
                    a != b && a != d && b != d) {
                    type2++;
                }

                if (a == e && b == d && c == f &&
                    a != b && a != c && b != c) {
                    type3++;
                }
            }
        }
    }

    cout << type1 << ' ' << type2 << ' ' << type3 << '\n';

    optimize_memory();
    return 0;
}
