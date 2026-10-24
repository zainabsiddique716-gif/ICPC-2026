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
