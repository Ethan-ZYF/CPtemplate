
#include <bits/extc++.h>
template <class T>
struct OrderedSet {
    using namespace __gnu_pbds;
    using Tree = tree<T, null_type, less_equal<T>, rb_tree_tag,
                      tree_order_statistics_node_update>;
    Tree t;

    OrderedSet() {}

    OrderedSet(initializer_list<T> v) {
        for (auto x : v) {
            t.insert(x);
        }
    }

    int size() {
        return t.size();
    }

    bool empty() {
        return t.empty();
    }

    void insert(T x) {
        t.insert(x);
    }

    void extract(T x) {
        t.erase(t.upper_bound(x));
    }

    T find_by_order(int i) {
        return *t.find_by_order(i);
    }

    int order_of_key(T x) {
        return t.order_of_key(x);
    }

    T prev(T x) {
        auto it = t.upper_bound(x);
        it--;
        return *it;
    }

    T next(T x) {
        return *t.lower_bound(x);
    }
};