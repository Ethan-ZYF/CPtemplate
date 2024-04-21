#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct LineTree {
    i64 n;

    struct line {
        i64 x1, x2, y;
        i64 tag;

        bool operator<(const line& t) const {
            return y < t.y;
        }
    };

    struct tree {
        i64 l, r;
        i64 cnt, len;
    };

    std::vector<line> L;
    std::vector<tree> tr;
    std::vector<i64> X;
    std::vector<std::tuple<i64, i64, i64, i64>> doc;

    LineTree(int _n = 2e5) : n(_n), L(n), tr(n * 8), X(n), doc(1) {}

    void add(int x1, int y1, int x2, int y2) {
        doc.emplace_back(x1, y1, x2, y2);
    }

    i64 work() {
        for (int i = 1; i < doc.size(); i++) {
            auto [x1, y1, x2, y2] = doc[i];
            L[i] = {x1, x2, y1, 1};
            L[i + doc.size() - 1] = {x1, x2, y2, -1};
            X[i] = x1, X[i + doc.size() - 1] = x2;
        }
        std::sort(L.begin() + 1, L.end());
        std::sort(X.begin() + 1, X.end());
        int tot = std::unique(X.begin() + 1, X.end()) - X.begin();
        build(1, 1, tot - 2);
        i64 ans = 0;
        for (i64 i = 1; i < n; i++) {
            int l = std::lower_bound(X.begin() + 1, X.begin() + tot, L[i].x1) - X.begin();
            int r = std::lower_bound(X.begin() + 1, X.begin() + tot, L[i].x2) - X.begin();
            apply(1, l, r - 1, L[i].tag);
            ans += tr[1].len * (L[i + 1].y - L[i].y);
        }
        return ans;
    }

    void build(int u, int l, int r) {
        tr[u] = {l, r, 0, 0};
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }

    void pushup(int u) {
        int l = tr[u].l, r = tr[u].r;
        if (tr[u].cnt)
            tr[u].len = X[r + 1] - X[l];
        else
            tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }

    void apply(int u, int l, int r, int tag) {
        if (l > tr[u].r || r < tr[u].l)
            return;
        if (l <= tr[u].l && r >= tr[u].r) {
            tr[u].cnt += tag;
            pushup(u);
            return;
        }
        apply(u << 1, l, r, tag);
        apply(u << 1 | 1, l, r, tag);
        pushup(u);
    }
};

void solve() {
    int n;
    std::cin >> n;

    LineTree line;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;

        line.add(x1, y1, x2, y2);
    }

    std::cout << line.work() << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int i64 = 1;
    // cin >> i64;
    for (int Task = 1; Task <= i64; Task++) {
        solve();
    }

    return 0;
}