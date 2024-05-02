template <typename T = int>
struct Trie {
    struct Node {
        array<Node*, 2> children{};
        int cnt = 0;
    };

    int HIGH_BIT;

    Trie(int HIGH_BIT = 30) : HIGH_BIT(HIGH_BIT) {}

    Node* root = new Node();

    void insert(T val) {
        Node* cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            T bit = (val >> i) & 1;
            if (cur->children[bit] == nullptr) {
                cur->children[bit] = new Node();
            }
            cur = cur->children[bit];
            cur->cnt++;
        }
    }

    void remove(T val) {
        Node* cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            cur = cur->children[(val >> i) & 1];
            cur->cnt--;
        }
    }

    T max_xor(T val) {
        Node* cur = root;
        T ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            T bit = (val >> i) & 1;
            if (cur->children[bit ^ 1] && cur->children[bit ^ 1]->cnt) {
                ans |= 1 << i;
                bit ^= 1;
            }
            cur = cur->children[bit];
        }
        return ans;
    }
};
