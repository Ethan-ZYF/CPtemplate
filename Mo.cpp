#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int N, Q;
    std::cin >> N >> Q;

    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    const int M = *std::max_element(A.begin(), A.end()) + 1;

    std::vector<int> freq(M);

    const int B = 400;
    std::vector<std::array<int, 3>> query(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        query[i] = {l, r, i};
    }
    std::sort(query.begin(), query.end(), [&](auto a, auto b) {
        if (a[0] / B != b[0] / B) {
            return a[0] < b[0];
        } else {
            return a[1] < b[1];
        }
    });
    i64 res = 0;
    std::vector<i64> ans(Q);

    auto add = [&](int x) {
        res += 1LL * freq[x] * (freq[x] - 1) / 2;
        freq[x] += 1;
    };
    auto del = [&](int x) {
        freq[x] -= 1;
        res -= 1LL * freq[x] * (freq[x] - 1) / 2;
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
        std::cout << ans[i] << "\n";
    }
}
