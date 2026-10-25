#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long a, b, c;
        cin >> a >> b >> c;

        long long sum = a + b + c;

        if (sum % 3 != 0) {
            cout << -1 << '\n';
            continue;
        }

        long long target = sum / 3;

        if (a == target && b == target && c == target)
            cout << 0 << '\n';
        else if (a == target || b == target || c == target)
            cout << 1 << '\n';
        else
            cout << 2 << '\n';
    }

    return 0;
}
