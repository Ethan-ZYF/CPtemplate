template <class Info, class Merge = std::plus<Info>>
struct ST {
    int n, lg;
    const Merge merge;
    std::vector<std::vector<Info>> st;
    ST(int n) : n(n), lg(std::__lg(n) + 1), merge(Merge()), st(lg, std::vector<Info>(n)) {}
    ST(std::vector<Info> init) : ST(init.size()) {
        // build(init);
        std::function<void(std::vector<Info>&)> build = [&](std::vector<Info>& a) {
            for (int i = 0; i < n; i++) {
                st[0][i] = a[i];
            }
            for (int j = 1; j < lg; j++) {
                for (int i = 0; i + (1 << j) <= n; i++) {
                    st[j][i] = merge(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
                }
            }
        };
        build(init);
    }
    Info query(int l, int r) {
        int j = std::__lg(r - l);
        return merge(st[j][l], st[j][r - (1 << j)]);
    }
};

struct Info {
    int x = 0;
};

Info operator+(const Info& a, const Info& b) {
    return Info{std::max(a.x, b.x)};
};