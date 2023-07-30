#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...)
#endif

class Solution {
   public:
    int makeTheIntegerZero(int num1, int num2) {
        for (int times = 1; times <= 100000; times++) {
            long long x = 0LL + num1 - 1LL * times * num2;
            if (x <= 0) {
                if (num2 >= 0)
                    break;
                else
                    continue;
            }
            int cnt = __builtin_popcountll(x);
            if (cnt <= times and x >= times) return times;
        }
        return -1;
    }
};

int main() {
    int x, y;
    cin >> x >> y;
    cout << Solution().makeTheIntegerZero(x, y) << endl;
}