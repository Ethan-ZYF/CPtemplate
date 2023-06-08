vector<pair<i64, int>> factor(i64 n) {
    vector<pair<i64, int>> res;
    for (i64 i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.emplace_back(i, 0);
            while (n % i == 0) {
                res.back().second++;
                n /= i;
            }
        }
    }
    if (n > 1) {
        res.emplace_back(n, 1);
    }
    return res;
}

struct Sieve {
    int n;
    std::vector<int> f, primes;
    Sieve(int n = 1) : n(n), f(n + 1) {
        f[0] = f[1] = -1;
        for (long long i = 2; i <= n; ++i) {
            if (f[i]) continue;
            primes.push_back(i);
            f[i] = i;
            for (long long j = i * i; j <= n; j += i) {
                if (!f[j]) f[j] = i;
            }
        }
    }
    bool is_prime(int x) {
        return f[x] == x;
    }
}sieve(1e7);