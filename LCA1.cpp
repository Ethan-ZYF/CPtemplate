struct LCA {
    int n, rt, lg;
    std::vector<std::vector<int>> g;
    std::vector<std::vector<int>> anc;
    std::vector<int> dep;

    LCA(int n) : n(n), g(n), anc(n, std::vector<int>(std::__lg(n) + 1, -1)), dep(n), lg(std::__lg(n) + 1) {}

    void add(int x, int y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }

    void dfs(int u, int fa) {
        anc[u][0] = fa;
        dep[u] = dep[fa] + 1;
        for (auto v : g[u]) {
            if (v != fa) {
                dep[v] = dep[u] + 1;
                dfs(v, u);
            }
        }
    }

    void build(int rt) {
        this->rt = rt;
        dfs(rt, -1);
        for (int i = 1; i < lg; i++) {
            for (int j = 0; j < n; j++) {
                if (anc[j][i - 1] != -1) {
                    anc[j][i] = anc[anc[j][i - 1]][i - 1];
                }
            }
        }
    }
    int kth(int x, int k) {
        for (; k; k &= k - 1)
            x = anc[x][__builtin_ctz(k)];
        return x;
    }

    int lca(int x, int y) {
        if (dep[x] > dep[y])
            std::swap(x, y);
        y = kth(y, dep[y] - dep[x]);
        if (y == x)
            return x;
        for (int i = anc[x].size() - 1; i >= 0; i--) {
            int px = anc[x][i], py = anc[y][i];
            if (px != py) {
                x = px;
                y = py;
            }
        }
        return anc[x][0];
    }
};