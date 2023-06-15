template <class Info,
          class Merge = std::plus<Info>>
struct Node {
    int left, right;
    Info info = 0;
    Node *left_child = nullptr, *right_child = nullptr;

    Node(int lb, int rb) {
        left = lb;
        right = rb;
    }

    void extend() {
        if (!left_child && left + 1 < right) {
            int t = (left + right) / 2;
            left_child = new Node(left, t);
            right_child = new Node(t, right);
        }
    }

    void modify(int k, int x) {
        extend();
        info += x;
        if (left_child) {
            if (k < left_child->right)
                left_child->modify(k, x);
            else
                right_child->modify(k, x);
        }
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