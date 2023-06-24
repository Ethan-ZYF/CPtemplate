template <class Info, class Tag>
struct Seg {
    int left, right;
    Info info;
    Tag tag;
    Seg *left_child = nullptr, *right_child = nullptr;

    Seg(int lb, int rb) {
        left = lb;
        right = rb;
    }

    void apply(const Tag& v) {
        info.sz = right - left;
        info.apply(v);
        tag.apply(v);
    }

    void push() {
        if (left_child) {
            left_child->apply(tag);
            right_child->apply(tag);
        }
        tag = Tag();
    }

    void pull() {
        info = left_child->info + right_child->info;
    }

    void extend() {
        if (!left_child && left + 1 < right) {
            int t = (left + right) / 2;
            left_child = new Seg(left, t);
            right_child = new Seg(t, right);
        }
    }

    void modify(int k, const Info& v) {
        if (left + 1 == right) {
            info = v;
            return;
        }
        extend();
        push();
        if (k < left_child->right) {
            left_child->modify(k, v);
        } else {
            right_child->modify(k, v);
        }
        pull();
    }

    Info rangeQuery(int l, int r) {
        if (l >= right || r <= left) {
            return Info();
        }
        if (l <= left && r >= right) {
            return info;
        }
        extend();
        push();
        return left_child->rangeQuery(l, r) + right_child->rangeQuery(l, r);
    }

    void rangeApply(int l, int r, const Tag& v) {
        if (l >= right || r <= left) {
            return;
        }
        if (l <= left && r >= right) {
            apply(v);
            return;
        }
        extend();
        push();
        left_child->rangeApply(l, r, v);
        right_child->rangeApply(l, r, v);
        pull();
    }

    Info query(int k) {
        return rangeQuery(k, k + 1);
    }

    Info allQuery() {
        return rangeQuery(left, right);
    }
};

struct Tag {
    i64 sum;

    Tag(i64 v = 0) : sum(v) {}

    void apply(const Tag& v) {
        sum += v.sum;
    }
};

struct Info {
    i64 sum;
    int sz;
    Info(i64 v = 0, int sz = 1) : sum(v), sz(sz) {}

    void apply(const Tag& v) {
        sum += 1LL * v.sum * sz;
    }
};

Info operator+(const Info& a, const Info& b) {
    return Info(a.sum + b.sum, a.sz + b.sz);
}