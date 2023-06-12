#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve() {
    int N, Q;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    const int M = *max_element(A.begin(), A.end()) + 1;

    vector<int> freq(M);
    const int B = sqrtl(N);
    cin >> Q;
    vector<array<int, 3>> query(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        query[i] = {l, r, i};
    }
    sort(query.begin(), query.end(), [&](auto a, auto b) {
        if (a[0] / B != b[0] / B) {
            return a[0] < b[0];
        } else {
            return a[1] < b[1];
        }
    });
    i64 res = 0;
    vector<i64> ans(Q);

    auto add = [&](int x) {
        res += freq[x] == 0;
        freq[x] += 1;
    };
    auto del = [&](int x) {
        freq[x] -= 1;
        res -= freq[x] == 0;
    };

    int L = 0, R = 0;
    for (auto [l, r, i] : query) {
        while (R < r) {
            add(A[R++]);
        }
        while (L > l) {
            add(A[--L]);
        }
        while (R > r) {
            del(A[--R]);
        }
        while (L < l) {
            del(A[L++]);
        }
        ans[i] = res;
    }
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    for (int Task = 1; Task <= T; Task++) {
        solve();
    }

    return 0;
}