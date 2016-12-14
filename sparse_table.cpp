template<const int& (*f)(const int&, const int&)>
class SparseTable {
    V(VI) sparse_table;
public:
    template<typename T>
    SparseTable(int N, const T &A) : sparse_table(21, VI(N)) {
        REP(i, N) {
            sparse_table[0][i] = A[i];
        }
        int k = 1;
        while ((1 << k) <= N) {
            REP1(i, 0, N - (1 << k)) {
                sparse_table[k][i] = f(sparse_table[k-1][i], sparse_table[k-1][i+(1<<(k-1))]);
            }
            k++;
        }
    }
    int query(int l, int r) {
        assert(l <= r);
        int k = sizeof(int) * 8 - 1 - __builtin_clz(r+1-l);
        return f(sparse_table[k][l], sparse_table[k][r+1-(1<<k)]);
    }
};
