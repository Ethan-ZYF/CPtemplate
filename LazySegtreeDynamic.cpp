template <class Info, class Tag>
struct Seg {
    i64 left, right;
    Info info;
    Tag tag;
    Seg *left_child = nullptr, *right_child = nullptr;

    Seg(i64 lb, i64 rb) {
        left = lb;
        right = rb;
        info = Info();
        tag = Tag();
    }

    void apply(const Tag& v) {
        info.apply(v);
        tag.apply(v);
    }

    void push() {
        if (left_child) left_child->apply(tag);
        if (right_child) right_child->apply(tag);
        tag = Tag();
    }

    void pull() {
        info = left_child->info + right_child->info;
    }

    void extend() {
        i64 mid = (left + right) / 2;
        if (not left_child) left_child = new Seg(left, mid);
        if (not right_child) right_child = new Seg(mid, right);
    }

    void modify(i64 k, const Info& v) {
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

    Info rangeQuery(i64 l, i64 r) {
        if (l >= right || r <= left) {
            return Info();
        }
        if (l <= left && r >= right) {
            return info;
        }
        push();
        Info ans = Info();
        if (left_child) ans = ans + left_child->rangeQuery(l, r);
        if (right_child) ans = ans + right_child->rangeQuery(l, r);
        return ans;
    }

    void rangeApply(i64 l, i64 r, const Tag& v) {
        if (l >= right || r <= left) {
            return;
        }
        if (l <= left && r >= right) {
            apply(v);
            return;
        }
        push();
        left_child->rangeApply(l, r, v);
        right_child->rangeApply(l, r, v);
        pull();
    }

    Info query(i64 k) {
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