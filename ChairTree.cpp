struct ChairTree {
    int n, tot;
    vector<int> ls, rs, root, sum;
    ChairTree(){};

    ChairTree(int _n) {
        init(_n);
    }

    void init(int _n) {
        this->n = _n;
        int tmp = n * 25;
        ls.resize(tmp);
        rs.resize(tmp);
        sum.resize(tmp);
        root.resize(n + 5);
        tot = 0;
        function<void(int&, int, int)> build = [&](int& u, int l, int r) {
            u = ++tot;
            if (l == r)
                return;
            int mid = (l + r) >> 1;
            build(ls[u], l, mid);
            build(rs[u], mid + 1, r);
        };
        build(root[0], 1, n);
    }

    void apply(int& u, int v, int l, int r, int p) {
        u = ++tot;
        ls[u] = ls[v], rs[u] = rs[v], sum[u] = sum[v] + 1;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (p <= mid)
            apply(ls[u], ls[v], l, mid, p);
        else
            apply(rs[u], rs[v], mid + 1, r, p);
    }

    int query(int u, int v, int l, int r, int k) {
        if (l == r)
            return l;
        int s = sum[ls[u]] - sum[ls[v]];
        int mid = (l + r) >> 1;
        if (s >= k)
            return query(ls[u], ls[v], l, mid, k);
        else
            return query(rs[u], rs[v], mid + 1, r, k - s);
    }

    int rangeQuery(int l, int r, int k) {
        return query(root[r], root[l - 1], 1, n, k);
    }
};