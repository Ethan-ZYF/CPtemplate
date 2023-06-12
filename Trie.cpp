struct Trie {
    static constexpr int ALPHABET = 26;

    struct Node {
        std::array<Node *, ALPHABET> next;
        bool is_end;
        int cnt;
        Node() : next(), is_end(false), cnt(0) {}
        constexpr int f(char c) {
            // modify this function and ALPHABET to support more characters
            if (c >= 'a' && c <= 'z') {
                return c - 'a';
            } else if (c >= 'A' && c <= 'Z') {
                return c - 'A';
            }
            assert(false);
        }
        Node *&operator[](char x) {
            return next[f(x)];
        }
    };

    Node *root;
    Trie() : root(new Node()) {}

    void add(const std::string &s) {
        Node *p = root;
        for (auto x : s) {
            if ((*p)[x] == nullptr) {
                (*p)[x] = new Node();
            }
            p = (*p)[x];
            p->cnt++;
        }
        p->is_end = true;
    }

    int count(const std::string &s) {
        Node *p = root;
        for (auto x : s) {
            if ((*p)[x] == nullptr) {
                return 0;
            }
            p = (*p)[x];
        }
        return p->cnt;
    }

    bool find(const std::string &s) {
        Node *p = root;
        for (auto x : s) {
            if ((*p)[x] == nullptr) {
                return false;
            }
            p = (*p)[x];
        }
        return p->is_end;
    }
};