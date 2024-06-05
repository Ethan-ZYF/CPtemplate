#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...)
#endif

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto& x : a)
        cin >> x;
    for (int i = 1; i < n; i++) {
        b[i] = gcd(a[i - 1], a[i]);
    }
    vector<int> L(n, 1), R(n, 1);
    for (int i = 1; i < n; i++) {
        L[i] = L[i - 1] && (b[i] >= b[i - 1]);
    }
    for (int i = n - 2; i >= 0; i--) {
        R[i] = R[i + 1] && (b[i] <= b[i + 1]);
    }
    debug(a);
    debug(b);
    debug(L);
    debug(R);
    // i, b[i - 1], b[i];
    // L[i - 2] && R[i + 1] && b[i - 2] <= gcd(a[i - 1], a[i + 1]) <= b[i + 1]
    bool ok = R[1] || L[n - 2] || L[n - 3] && gcd(a[n - 3], a[n - 1]) >= b[n - 3];
    for (int i = 1; i < n - 2; i++) {
        ok |= L[i - 1] && R[i + 2] && b[i - 1] <= gcd(a[i - 1], a[i + 1]) && gcd(a[i - 1], a[i + 1]) <= b[i + 2];
    }
    debug(ok);
    cout << (ok ? "YES" : "NO") << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int T = 1;
    cin >> T;
    for (int Task = 1; Task <= T; Task++) {
        debug(Task);
        solve();
    }

    return 0;
}