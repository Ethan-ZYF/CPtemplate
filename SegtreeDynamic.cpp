template <class Info>
struct Seg {
    int left, right;
    Info info;
    Seg *left_child = nullptr, *right_child = nullptr;

    Seg(int lb, int rb) {
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
        info = left_child->info + right_child->info;
    }

    void modify(int k, const Info& v) {
        if (left + 1 == right) {
            info = v;
            return;
        }
        extend();
        if (k < left_child->right) {
            left_child->modify(k, v);
        } else {
            right_child->modify(k, v);
        }
        pull();
    }

    Info rangeQuery(int lq, int rq) {
        if (lq <= left && right <= rq)
            return info;
        if (std::max(left, lq) >= std::min(right, rq))
            return 0;
        extend();
        return left_child->rangeQuery(lq, rq) + right_child->rangeQuery(lq, rq);
    }
};