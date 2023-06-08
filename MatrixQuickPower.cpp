constexpr int MOD = 1e9 + 7;

vector<vector<i64>> operator*(const vector<vector<i64>> &a, const vector<vector<i64>> &b) {
    int n = a.size();
    vector<vector<i64>> c(n, vector<i64>(n));
    for (i64 i = 0; i < n; i++)
        for (i64 k = 0; k < n; k++)
            for (i64 j = 0; j < n; j++)
                c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % MOD;
    return c;
}

vector<vector<i64>> power(vector<vector<i64>> a, i64 k) {
    int n = a.size();
    vector<vector<i64>> res(n, vector<i64>(n));
    for (int i = 0; i < n; i++)
        res[i][i] = 1;
    while (k) {
        if (k & 1)
            res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}