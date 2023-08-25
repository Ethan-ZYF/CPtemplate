constexpr int MX = 1e9;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd() { return rng() % MX; }

struct Treap {
    struct Node {
        int key, rnk, siz, cnt;
        Node *l, *r;
        Node(int key) : key(key), rnk(rnd()), siz(1), cnt(1), l(nullptr), r(nullptr) {}

        void update() {
            siz = cnt + (l ? l->siz : 0) + (r ? r->siz : 0);
        }
    };

    Node *root = nullptr;
    int prev_tmp, next_tmp;
    Treap() {}

    void rotateLeft(Node *&cur) {
        Node *tmp = cur->r;
        cur->r = tmp->l;
        tmp->l = cur;
        cur->update();
        tmp->update();
        cur = tmp;
    }

    void rotateRight(Node *&cur) {
        Node *tmp = cur->l;
        cur->l = tmp->r;
        tmp->r = cur;
        cur->update();
        tmp->update();
        cur = tmp;
    }

    void insert(Node *&cur, int key) {
        if (!cur) {
            cur = new Node(key);
            return;
        }
        if (key == cur->key) {
            cur->cnt++;
            cur->siz++;
            return;
        }
        if (key < cur->key) {
            insert(cur->l, key);
            if (cur->l->rnk > cur->rnk) {
                rotateRight(cur);
            }
            cur->update();
        } else {
            insert(cur->r, key);
            if (cur->r->rnk > cur->rnk) {
                rotateLeft(cur);
            }
            cur->update();
        }
    }

    void remove(Node *&cur, int key) {
        if (!cur) {
            return;
        }
        if (key == cur->key) {
            if (cur->cnt > 1) {
                cur->cnt--;
                cur->siz--;
                return;
            }
            if (!cur->l && !cur->r) {
                delete cur;
                cur = nullptr;
                return;
            }
            if (!cur->l) {
                Node *tmp = cur;
                cur = cur->r;
                delete tmp;
                return;
            }
            if (!cur->r) {
                Node *tmp = cur;
                cur = cur->l;
                delete tmp;
                return;
            }
            if (cur->l->rnk > cur->r->rnk) {
                rotateRight(cur);
                remove(cur->r, key);
            } else {
                rotateLeft(cur);
                remove(cur->l, key);
            }
            cur->update();
        } else if (key < cur->key) {
            remove(cur->l, key);
            cur->update();
        } else {
            remove(cur->r, key);
            cur->update();
        }
    }

    int orderOfKey(Node *&cur, int key) {
        int less_num = cur->l ? cur->l->siz : 0;
        if (key == cur->key) {
            return less_num + 1;
        }
        if (key < cur->key) {
            return cur->l ? orderOfKey(cur->l, key) : 1;
        } else {
            return cur->r ? less_num + cur->cnt + orderOfKey(cur->r, key) : cur->cnt + 1;
        }
    }

    int findByOrder(Node *&cur, int k) {
        int less_num = cur->l ? cur->l->siz : 0;
        if (k <= less_num) {
            return cur->l ? findByOrder(cur->l, k) : cur->key;
        }
        if (k <= less_num + cur->cnt) {
            return cur->key;
        }
        return cur->r ? findByOrder(cur->r, k - less_num - cur->cnt) : MX;
    }

    int prev(Node *&cur, int key) {
        if (!cur) {
            return -MX;
        }
        if (key <= cur->key) {
            return cur->l ? prev(cur->l, key) : -MX;
        } else {
            prev_tmp = cur->key;
            if (cur->r) prev(cur->r, key);
            return prev_tmp;
        }
    }

    int next(Node *&cur, int key) {
        if (!cur) {
            return MX;
        }
        if (key < cur->key) {
            next_tmp = cur->key;
            if (cur->l) next(cur->l, key);
            return next_tmp;
        } else {
            return cur->r ? next(cur->r, key) : MX;
        }
    }
    int size() {
        return root ? root->siz : 0;
    }
    void insert(int key) {
        insert(root, key);
    }
    void remove(int key) {
        remove(root, key);
    }
    int orderOfKey(int key) {
        return orderOfKey(root, key);
    }
    int findByOrder(int k) {
        return findByOrder(root, k);
    }

    int prev(int key) {
        return prev(root, key);
    }

    int next(int key) {
        return next(root, key);
    }
};