template <int n>
struct EulerTotient {
    vector<int> phi;

    EulerTotient() : phi(n + 1) {
        iota(phi.begin(), phi.end(), 0);
        for (int i = 2; i <= n; i++) {
            if (phi[i] == i) {
                for (int j = i; j <= n; j += i)
                    phi[j] -= phi[j] / i;
            }
        }
    }

    int operator[](int x) const {
        if (x <= n)
            return phi[x];
        int result = x;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                while (x % i == 0)
                    x /= i;
                result -= result / i;
            }
        }
        if (x > 1)
            result -= result / x;
        return result;
    }
};

constexpr int mxn = 1e5 + 1;
EulerTotient<mxn> phi;