struct PresidentTree {
    struct Node {
        int l, r, cnt;
    };

    int n, cntNodes = 0;
    std::vector<int> root;
    std::vector<Node> tr;

    PresidentTree(int n) : n(n) {
        root.resize(n + 1);
        tr.resize(4 * n + 17 * n);
    }

    void modify(int& u, int v, int l, int r, int x) {
        u = ++cntNodes;
        tr[u] = tr[v];
        tr[u].cnt++;
        if (l == r)
            return;
        int mid = (l + r) / 2;
        if (x <= mid)
            modify(tr[u].l, tr[v].l, l, mid, x);
        else
            modify(tr[u].r, tr[v].r, mid + 1, r, x);
    }

    int kth(int u, int v, int l, int r, int k) {
        if (l == r)
            return l;
        int res = tr[tr[v].l].cnt - tr[tr[u].l].cnt;
        int mid = (l + r) / 2;
        if (k <= res)
            return kth(tr[u].l, tr[v].l, l, mid, k);
        else
            return kth(tr[u].r, tr[v].r, mid + 1, r, k - res);
    }
};
