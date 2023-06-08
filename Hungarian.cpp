/*
 * @author cuiaoxiang
 * https://codeforces.com/profile/cuiaoxiang
 */
struct Hungarian {
    int n;
    std::vector<std::vector<int>> a;
    std::vector<int> d;
    std::vector<bool> visit;
    bool path(int u) {
        for (auto& v : a[u]) {
            if (visit[v]) continue;
            visit[v] = true;
            if (d[v] < 0 || path(d[v])) {
                d[v] = u;
                return true;
            }
        }
        return false;
    }
    Hungarian(int n, int m) : n(n), a(n), d(m, -1), visit(m) {}
    void add(int x, int y) {
        a[x].push_back(y);
    }
    int solve() {
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            std::fill(visit.begin(), visit.end(), false);
            ret += path(i);
        }
        return ret;
    }
};