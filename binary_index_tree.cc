// index starts with 1
template<class T>
class BIT {
public:
    vector<T> bit;
    BIT() {}
    BIT(int n): bit(n+1) {}
    T sum(int i) {
        assert(i >= 0);
        if (i >= bit.size()) {
            return sum(bit.size() - 1);
        }
        T s = 0;
        while(i > 0) {
            s += bit.at(i);
            i &= i - 1;
        }
        return s;
    }
    void add(int i, T x) {
        assert(i > 0 && i < bit.size());
        while(i < bit.size()) {
            bit.at(i) += x;
            i += i & -i;
        }
    }
    void resize(int n) {
        bit.resize(n+1);
    }
};

// 2D
int bit[505][505];

int N, M;

void add(int x, int y, int w) {
    for(int i = x; i <= N; i += i & -i)
        for(int j = y; j <= M; j += j & -j)
            bit[i][j] ^= w;
}

int sum(int x, int y) {
    int ans = 0;
    for(int i = x; i > 0; i &= i - 1)
        for(int j = y; j > 0; j &= j - 1)
            ans ^= bit[i][j];
    return ans;
}

int sum(int x1, int y1, int x2, int y2) {
    x1--; y1--;
    return sum(x2, y2) ^ sum(x1, y2) ^ sum(x2, y1) ^ sum(x1, y1);
}

// 3D

LL bit[101][101][101];

int N;

void add(int x, int y, int z, LL w) {
    for(int i = x; i <= N; i += i & -i)
        for(int j = y; j <= N; j += j & -j)
            for(int k = z; k <= N; k += k & -k)
                bit[i][j][k] += w;
}

LL sum(int x, int y, int z) {
    LL ans = 0;
    for(int i = x; i > 0; i &= i - 1)
        for(int j = y; j > 0; j &= j - 1)
            for(int k = z; k > 0; k &= k - 1)
                ans += bit[i][j][k];
    return ans;
}

LL sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    x1--; y1--; z1--;
    return sum(x2, y2, z2) - sum(x1, y2, z2) - sum(x2, y1, z2) - sum(x2, y2, z1)
        + sum(x1, y1, z2) + sum(x1, y2, z1) + sum(x2, y1, z1) - sum(x1, y1, z1);
}

LL query(int x, int y, int z) {
    return sum(x, y, z, x, y, z);
}
