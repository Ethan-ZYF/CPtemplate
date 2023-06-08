template <class T = i64>
struct Dijkstra {
    int n;
    const T INF;
    using pit = std::pair<int, T>;
    using G = std::vector<std::vector<pit>>;
    G g;
    std::vector<int> parent;
    Dijkstra(int n, const T& INF = 1e18) : n(n), g(n), INF(INF), parent(n, -1) {}
    void add(int a, int b, T c) {
        g[a].emplace_back(b, c);
    }
    std::vector<T> run(int s) {
        std::vector<T> d(n, INF);
        using pti = std::pair<T, int>;
        std::priority_queue<pti, std::vector<pti>, std::greater<>> q;
        d[s] = 0;
        q.emplace(d[s], s);
        while (q.size()) {
            auto [dist, u] = q.top();
            q.pop();
            if (dist != d[u]) continue;
            for (auto& [v, w] : g[u]) {
                T fina = d[u] + w;
                if (d[v] > fina) {
                    d[v] = fina;
                    parent[v] = u;
                    q.emplace(d[v], v);
                }
            }
        }
        return d;
    }
    std::vector<int> get_path(int t) {
        std::vector<int> path;
        for (; t != -1; t = parent[t]) {
            path.push_back(t);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
    bool has_path(int t) {
        return parent[t] != -1;
    }
};