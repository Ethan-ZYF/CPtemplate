#include <bits/extc++.h>
using namespace __gnu_pbds;
tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> t;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int q, opt, x;
    cin >> q;
    while (q--) {
        cin >> opt >> x;
        if (opt == 1) {
            t.insert(x);
        } else if (opt == 2) {
            t.erase(t.upper_bound(x));
        } else if (opt == 3) {
            cout << t.order_of_key(x) + 1 << endl;
        } else if (opt == 4) {
            cout << *t.find_by_order(x - 1) << endl;
        } else if (opt == 5) {
            auto it = t.upper_bound(x);
            cout << *--it << endl;
        } else {
            auto it = t.lower_bound(x);
            cout << *it << endl;
        }
    }
    return 0;
}