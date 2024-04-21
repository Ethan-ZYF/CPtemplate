bool isprime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int findPrime(int n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}

constexpr int BASE = 131;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const int P = findPrime(rng() % 900000000 + 100000000);

struct StringRollingHash {
    std::vector<i64> hash, base, mod;

    StringRollingHash(const std::string& s) {
        int n = s.size();
        hash.resize(n + 1);
        base.resize(n + 1);
        mod.resize(n + 1);
        base[0] = 1;
        mod[0] = 1;
        for (int i = 1; i <= n; i++) {
            base[i] = (base[i - 1] * BASE) % P;
            mod[i] = (mod[i - 1] * P) % P;
        }
        for (int i = 0; i < n; i++) {
            hash[i + 1] = (hash[i] * BASE + s[i]) % P;
        }
    }

    i64 get(int l, int r) {
        return (hash[r] - (hash[l] * base[r - l]) % P + P) % P;
    }

    i64 get(const std::string& s) {
        i64 h = 0;
        for (char c : s) {
            h = (h * BASE + c) % P;
        }
        return h;
    }
};