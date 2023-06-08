#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...)
#endif

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), c2(n + 1), c5(n + 1);
    int cnt2 = 0, cnt5 = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        while (a[i] % 2 == 0) {
            a[i] /= 2;
            cnt2++;
        }
        while (a[i] % 5 == 0) {
            a[i] /= 5;
            cnt5++;
        }
        c2[i + 1] = cnt2;
        c5[i + 1] = cnt5;
    }
    debug(c2);
    debug(c5);
    // 对于每个l, 找到最小的r1, 使得min(c2[r1] - c2[l], c5[r1] - c5[l]) >= k
    // 对于每个l, 找到最大的r2, 使得min(c2[r2] - c2[l], c5[r2] - c5[l]) >= k
    // ans += r2 - r1 + 1
    auto check = [&](int l, int r) {
        return min(c2[r] - c2[l], c5[r] - c5[l]) == k;
    };
    i64 ans = 0;
    for (int l = 0; l < n; l++) {
        int lo = l, hi = n + 1;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (min(c2[mid] - c2[l], c5[mid] - c5[l]) >= k) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        int r1 = hi;
        lo = l, hi = n + 1;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (min(c2[mid] - c2[l], c5[mid] - c5[l]) > k) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        int r2 = lo;
        // debug(l, r1, r2);
        if (r1 <= r2 and check(l, r1) and check(l, r2)) {
            debug(l, r1, r2);
            ans += r2 - r1 + 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int Task = 1; Task <= T; Task++) {
        debug(Task);
        solve();
    }

    return 0;
}