struct TopologicalSort {
    std::vector<int> get_rank(int n, std::vector<std::pair<int, int>>& edges) {
        std::vector<std::vector<int>> dct(n);
        std::vector<int> degree(n, 0);
        for (auto& edge : edges) {
            degree[edge.second]++;
            dct[edge.first].push_back(edge.second);
        }
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        std::vector<int> visit(n, -1);
        int step = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int i = q.front();
                q.pop();
                visit[i] = step;
                for (int j : dct[i]) {
                    degree[j]--;
                    if (degree[j] == 0) {
                        q.push(j);
                    }
                }
            }
            step++;
        }
        return visit;
    }

    std::vector<int> count_dag_path(int n, std::vector<std::pair<int, int>>& edges) {
        std::vector<std::vector<int>> edge(n);
        std::vector<int> degree(n, 0);
        for (auto& e : edges) {
            edge[e.first].push_back(e.second);
            degree[e.second]++;
        }
        std::vector<int> cnt(n, 0);
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 0) {
                q.push(i);
                cnt[i] = 1;
            }
        }
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            for (int j : edge[i]) {
                degree[j]--;
                cnt[j] += cnt[i];
                if (degree[j] == 0) {
                    q.push(j);
                }
            }
        }
        return cnt;
    }

    bool is_topology_unique(std::vector<std::vector<int>>& dct, std::vector<int>& degree, int n) {
        std::vector<int> ans;
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            if (q.size() > 1) {
                return false;
            }
            int i = q.front();
            q.pop();
            ans.push_back(i);
            for (int j : dct[i]) {
                degree[j]--;
                if (degree[j] == 0) {
                    q.push(j);
                }
            }
        }
        return true;
    }

    bool is_topology_loop(std::vector<std::vector<int>>& edge, std::vector<int>& degree, int n) {
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            for (int j : edge[i]) {
                degree[j]--;
                if (degree[j] == 0) {
                    q.push(j);
                }
            }
        }
        return std::any_of(degree.begin(), degree.end(), [](int deg) { return deg != 0; });
    }

    std::vector<int> bfs_topologic_order(int n, std::vector<std::vector<int>>& dct, std::vector<int>& degree) {
        std::vector<int> order(n, 0);
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        int index = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int i = q.front();
                q.pop();
                order[i] = index++;
                for (int j : dct[i]) {
                    degree[j]--;
                    if (degree[j] == 0) {
                        q.push(j);
                    }
                }
            }
        }
        if (std::any_of(degree.begin(), degree.end(), [](int deg) { return deg > 0; })) {
            return {};
        }
        return order;
    }
};
