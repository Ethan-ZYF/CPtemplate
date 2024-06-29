struct persistent_tree {
    struct node;
    using iter = std::vector<node>::iterator;

    struct node {
        int a, b;
        iter left, right;
        int sum, lsum, rsum;

        void pushup() {
            lsum = left->lsum;
            if (left->sum == left->b - left->a) lsum = left->sum + right->lsum;
            rsum = right->rsum;
            if (right->sum == right->b - right->a) rsum = right->sum + left->rsum;
            sum = std::max(left->sum, right->sum);
            sum = std::max(sum, left->rsum + right->lsum);
        }
    };

    std::vector<iter> root;
    std::vector<node> pool;
    iter last;

    iter _build(int a, int b) {
        iter cur = last++;
        cur->a = a;
        cur->b = b;
        if (a + 1 == b) {
            cur->sum = cur->lsum = cur->rsum = 0;
            return cur;
        }
        cur->left = _build(a, (a + b) / 2);
        cur->right = _build((a + b) / 2, b);
        cur->pushup();
        return cur;
    }

    void init(int n, int m) {
        root.resize(m + 1);
        int lev = 0;
        for (; (1 << lev) < n; ++lev)
            ;
        ++lev;
        pool.resize(n * 2 + m * lev);
        last = pool.begin();
        root[0] = _build(0, n);
    }

    void insert(iter pre, iter& cur, int pos) {
        cur = last++;
        *cur = *pre;
        if (cur->a + 1 == cur->b) {
            cur->lsum = cur->rsum = cur->sum = 1;
            return;
        }
        if ((cur->a + cur->b) / 2 > pos) {
            insert(pre->left, cur->left, pos);
        } else {
            insert(pre->right, cur->right, pos);
        }
        cur->pushup();
    }

    std::array<int, 3> query(iter cur, int L, int R) {
        if (cur->a >= L && cur->b <= R) {
            return {cur->sum, cur->lsum, cur->rsum};
        }
        int mid = (cur->a + cur->b) / 2;
        if (R <= mid) return query(cur->left, L, R);
        if (L >= mid) return query(cur->right, L, R);
        auto [usum, ulsum, ursum] = query(cur->left, L, R);
        auto [vsum, vlsum, vrsum] = query(cur->right, L, R);
        int sum = std::max(std::max(usum, vsum), ursum + vlsum);
        int lsum = ulsum;
        if (mid - std::max(cur->a, L) == usum) lsum = usum + vlsum;
        int rsum = vrsum;
        if (std::min(cur->b, R) - mid == vsum) rsum = vsum + ursum;
        return {sum, lsum, rsum};
    }
};