auto bfs = [&](auto &adj_) {
    std::vector<int> vis(N, -1);
    vis[0] = 0;
    std::queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (auto y : adj_[x]) {
            if (vis[y] == -1) {
                vis[y] = vis[x] + 1;
                q.push(y);
            }
        }
    }
    return vis;
};