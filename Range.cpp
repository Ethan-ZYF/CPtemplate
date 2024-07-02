struct range {
    struct Iterator {
        using iterator_category = std::random_access_iterator_tag;
        using value_type = i64;
        using difference_type = ptrdiff_t;
        using pointer = i64;
        using reference = i64&;
        i64 val, d;
        Iterator(){};
        Iterator(i64 val, i64 d) : val(val), d(d){};

        value_type operator*() const {
            return val;
        }

        Iterator& operator++() {
            return val += d, *this;
        }

        difference_type operator-(const Iterator& other) const {
            return (val - other.val) / d;
        }

        bool operator==(const Iterator& other) const {
            return val == other.val;
        }
    };

    Iterator Begin, End;
    range(i64 n) : Begin(0, 1), End(max(n, i64{0}), 1){};

    range(i64 a, i64 b, i64 d = i64(1)) : Begin(a, d), End(b, d) {
        i64 cnt = (b - a) / d + bool((b - a) % d);
        End.val = a + max(cnt, i64(0)) * d;
    };

    Iterator begin() const {
        return Begin;
    }

    Iterator end() const {
        return End;
    };

    operator vector<Iterator::value_type>() {
        return vector(begin(), end());
    }
};