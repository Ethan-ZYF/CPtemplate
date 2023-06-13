using i128 = __int128;
std::istream &operator>>(std::istream &is, i128 &i) {
    i64 _i;
    is >> _i;
    i = _i;
    return is;
}
std::ostream &operator<<(std::ostream &os, const i128 &i) {
    if (i == 0) {
        return os << "0";
    }
    std::string s;
    for (auto j = i; j; j /= 10) {
        s += '0' + j % 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}