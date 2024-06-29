struct Discretization {
    std::vector<int> a;

    Discretization() {}

    template <typename T>
    Discretization(const std::vector<T>& b) {
        a = b;
        std::sort(a.begin(), a.end());
        a.erase(std::unique(a.begin(), a.end()), a.end());
    }

    int size() const {
        return a.size();
    }

    int operator[](int i) const {
        return std::lower_bound(a.begin(), a.end(), i) - a.begin();
    }
};