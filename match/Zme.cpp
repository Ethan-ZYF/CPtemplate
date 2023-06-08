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
    std::cin >> n >> k;
    int64_t ans = 0;
    std::unordered_map<int, std::vector<int>> tp, fp;
    tp[0].push_back(0);
    fp[0].push_back(0);
    for (int i = 0, t = 0, f = 0; i < n; i++) {
        int x;
        std::cin >> x;
        for (; x && x % 2 == 0; x /= 2, t++) {
        }
        for (; x && x % 5 == 0; x /= 5, f++) {
        }
        ans += std::max(
            std::upper_bound(tp[t - k].begin(), tp[t - k].end(), f - k) - tp[t - k].begin(),
            std::upper_bound(fp[f - k].begin(), fp[f - k].end(), t - k) - fp[f - k].begin());
        tp[t].push_back(f);
        fp[f].push_back(t);
    }
    std::cout << ans << "\n";
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