using i128 = __int128;

std::ostream &operator<<(std::ostream &os, i128 n) {
    std::string s;
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}

std::istream &operator>>(std::istream &is, i128 &n) {
    std::string s;
    is >> s;
    n = 0;
    for (char c : s)
        n = n * 10 + c - '0';
    return is;
}