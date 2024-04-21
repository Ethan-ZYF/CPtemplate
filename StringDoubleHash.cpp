template <int N>
struct StringHash {
    const int base[2] = {13331, 131};
    const int mod[2] = {1000000007, 1000000009};
    std::vector<std::array<int, N>> p, h;

    StringHash() = default;

    StringHash(const std::string& s) {
        int n = s.size() - 1;
        p.resize(n + 1);
        h.resize(n + 1);
        fill(p[0].begin(), p[0].end(), 1);
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < N; j++)
                p[i][j] = 1ll * p[i - 1][j] * base[j] % mod[j];
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < N; j++)
                h[i][j] = (1ll * h[i - 1][j] * base[j] + s[i]) % mod[j];
    }

    std::array<int, N> query(int l, int r) {
        assert(r >= l - 1);
        std::array<int, N> ans;
        if (l > r)
            return {0, 0};
        for (int i = 0; i < N; i++) {
            ans[i] = (h[r][i] - 1ll * h[l - 1][i] * p[r - l + 1][i] % mod[i] + mod[i]) % mod[i];
        }
        return ans;
    }
};

//sameple StringHash<N> hsh(s);