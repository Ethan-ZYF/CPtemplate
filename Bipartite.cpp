struct Bipartite {
    std::vector<std::vector<int>> g;
    std::vector<int> color;
    Bipartite(int n) : g(n), color(n, -1) {}

    void add(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool dfs(int u, int c) {
        color[u] = c;
        for (auto v : g[u]) {
            if (color[v] == -1) {
                if (!dfs(v, c ^ 1)) return false;
            } else if (color[v] == color[u]) {
                return false;
            }
        }
        return true;
    }

    bool work() {
        for (int i = 0; i < g.size(); i++) {
            if (color[i] == -1) {
                if (!dfs(i, 0)) return false;
            }
        }
        return true;
    }

    std::vector<int> get_color() {
        return color;
    }
};