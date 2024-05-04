template <int n>
struct Divisors {
    vector<vector<int>> d;

    Divisors() : d(n + 1) {
        for (int i = 1; i < n; i++) {
            for (int j = i; j < n; j += i) {
                d[j].push_back(i);
            }
        }
    }

    const vector<int>& operator[](int x) const {
        return d[x];
    }
};

constexpr int mxn = 1e5;
Divisors<mxn> divs;