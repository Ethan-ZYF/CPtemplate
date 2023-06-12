struct LCA {
    int n;
    std::vector<std::vector<int>> g;
    std::vector<int> sz, top, son, d, f;
    LCA(int n = 0) : g(n), sz(n), top(n), son(n), d(n), f(n) {}
    void add(int a, int b) {
        g[a].push_back(b), g[b].push_back(a);
    }
    void build(int u) {
        auto dfs = [&](auto &self, int u, int p, int dep) -> void {
            d[u] = dep, f[u] = p, sz[u] = 1, son[u] = -1;
            for (int &v : g[u]) {
                if (v == p) continue;
                self(self, v, u, dep + 1);
                sz[u] += sz[v];
                if (son[u] == -1 || sz[son[u]] < sz[v]) {
                    son[u] = v;
                }
            }
        };
        auto dfs2 = [&](auto &self, int u, int tp) -> void {
            top[u] = tp;
            for (int &v : g[u]) {
                if (v == f[u]) continue;
                if (v == son[u])
                    self(self, v, tp);
                else
                    self(self, v, v);
            }
        };
        dfs(dfs, u, -1, 0);
        dfs2(dfs2, u, u);
    }
    int lca(int x, int y) {
        while (top[x] != top[y]) {
            if (d[top[x]] < d[top[y]]) std::swap(x, y);
            x = f[top[x]];
        }
        return d[x] < d[y] ? x : y;
    }
};