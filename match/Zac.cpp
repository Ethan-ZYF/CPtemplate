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
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++) {
        vector<int> aa = a;
        aa.erase(aa.begin() + i);
        vector<int> b(n - 1);
        for (int j = 1; j < n - 1; j++) {
            b[j] = gcd(aa[j - 1], aa[j]);
        }
        if(is_sorted(b.begin(), b.end())) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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