struct Hash {
    unsigned long long hash;
    Hash() : hash(14695981039346656037ull) {}
    void push(char data) {
        hash ^= data;
        hash *= 1099511628211ull;
    }
};