std::vector<int> GospersHack(int k, int n) {
    int cur = (1 << k) - 1;
    int limit = (1 << n);
    std::vector<int> res;
    while (cur < limit) {
        res.push_back(cur);
        // do something
        int lb = cur & -cur;
        int r = cur + lb;
        cur = ((r ^ cur) >> __builtin_ctz(lb) + 2) | r;
        // 或：cur = (((r ^ cur) >> 2) / lb) | r;
    }
    return res;
}