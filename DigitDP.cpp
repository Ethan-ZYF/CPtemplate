i64 dp(i64 n) {
    auto s = to_string(n);
    i64 m = s.length(), memo[m][10];
    memset(memo, -1, sizeof(memo));  // -1 表示没有计算过
    function<i64(int, int, bool, bool)> f = [&](int i, int last, bool is_limit, bool is_num) -> i64 {
        if (i == m)
            return is_num;  // is_num 为 true 表示得到了一个合法数字
        if (!is_limit && is_num && memo[i][last] != -1)
            return memo[i][last];
        i64 res = 0;
        if (!is_num)  // 可以跳过当前数位
            res = f(i + 1, last, false, false);
        int up = is_limit ? s[i] - '0' : 9;  // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[i]（否则就超过 n 啦）
        for (int d = 1 - is_num; d <= up; ++d)
            if (last != d)  // 不能填和上一位一样的数字
                res += f(i + 1, d, is_limit && d == up, true);
        if (!is_limit && is_num)
            memo[i][last] = res;
        return res;
    };
    return f(0, -1, true, false);
}

i64 query(i64 a, i64 b) {
    assert(a <= b);
    if (a == 0) {
        return dp(b) + 1;
    } else {
        return dp(b) - dp(a - 1);
    }
}