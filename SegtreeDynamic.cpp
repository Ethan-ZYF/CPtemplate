template <typename Info>
struct Seg {
    i64 left, right;
    Info info;
    Seg *left_child = nullptr, *right_child = nullptr;

    Seg(i64 lb, i64 rb) {
        left = lb;
        right = rb;
    }

    void extend() {
        if (!left_child && left + 1 < right) {
            int t = (left + right) / 2;
            left_child = new Seg(left, t);
            right_child = new Seg(t, right);
        }
    }

    void pull() {
        info = Info();
        if (left_child)
            info = info + left_child->info;
        if (right_child)
            info = info + right_child->info;
    }

    void modify(i64 k, const Info& v) {
        if (left + 1 == right) {
            info = v;
            return;
        }
        i64 mid = (left + right) / 2;
        if (k < mid) {
            if (!left_child)
                left_child = new Seg(left, mid);
            left_child->modify(k, v);
        } else {
            if (!right_child)
                right_child = new Seg(mid, right);
            right_child->modify(k, v);
        }
        pull();
    }

    Info rangeQuery(i64 lq, i64 rq) {
        if (lq <= left && right <= rq)
            return info;
        if (max(left, lq) >= min(right, rq))
            return Info();
        Info ans;
        if (left_child)
            ans = ans + left_child->rangeQuery(lq, rq);
        if (right_child)
            ans = ans + right_child->rangeQuery(lq, rq);
        return ans;
    }
};

constexpr i64 INF = 1e9 + 5;

struct Info {
    i64 x;

    Info(i64 x = 0) : x(x) {}
};

Info operator+(const Info& a, const Info& b) {
    return Info(a.x + b.x);
}