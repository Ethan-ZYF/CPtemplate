constexpr i64 INF = 1e8;
constexpr i64 base1 = 131, base2 = 13331;
constexpr i64 p1 = 1e9 + 7, p2 = 1e9 + 9;

struct DoubleStringHash {
    vector<i64> h1, h2, w1, w2;
    void init(string s) {
        int len = s.size();
        s = " " + s;
        h1.resize(len + 1), w1.resize(len + 1);
        h2.resize(len + 1), w2.resize(len + 1);
        h1[0] = 0, w1[0] = 1;
        h2[0] = 0, w2[0] = 1;
        for (int i = 1; i <= len; i++) {
            h1[i] = (h1[i - 1] * base1 + s[i]) % p1, w1[i] = w1[i - 1] * base1 % p1;
            h2[i] = (h2[i - 1] * base2 + s[i]) % p2, w2[i] = w2[i - 1] * base2 % p2;
        }
    }
    inline i64 get(int l, int r) {
        i64 h1 = (this->h1[r] - this->h1[l - 1] * w1[r - l + 1] % p1 + p1) % p1;
        i64 h2 = (this->h2[r] - this->h2[l - 1] * w2[r - l + 1] % p2 + p2) % p2;
        return h1 * p2 + h2;
    }
};

i64 string_hash(string s) {
    i64 h1 = 0, h2 = 0;
    for (char c : s) {
        h1 = (h1 * base1 + c) % p1;
        h2 = (h2 * base2 + c) % p2;
    }
    return h1 * p2 + h2;
}